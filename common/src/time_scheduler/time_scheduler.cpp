#include "time_scheduler.h"
#include "logger/logger.h"
#include <algorithm>

namespace common {

TimeScheduler::TimeScheduler()
    : running_(false), stopped_(false), next_task_id_(1) {
    Logger::info("TimeScheduler created");
}

TimeScheduler::~TimeScheduler() {
    stop();
    Logger::info("TimeScheduler destroyed");
}

void TimeScheduler::start() {
    if (running_.exchange(true)) {
        Logger::warn("TimeScheduler already running");
        return;
    }
    stopped_ = false;
    scheduler_thread_ = std::thread(&TimeScheduler::schedulerThread, this);
    Logger::info("TimeScheduler started");
}

void TimeScheduler::stop() {
    if (!running_.exchange(false)) {
        return;
    }
    stopped_ = true;
    cv_.notify_all();
    if (scheduler_thread_.joinable()) {
        scheduler_thread_.join();
    }
    Logger::info("TimeScheduler stopped");
}

TaskId TimeScheduler::scheduleOnce(const TaskCallback& callback,
                                   std::chrono::milliseconds delay) {
    auto task = std::make_shared<Task>();
    task->id = generateTaskId();
    task->callback = callback;
    task->type = ScheduleType::ONCE;
    task->next_run = std::chrono::steady_clock::now() + delay;

    {
        std::lock_guard<std::mutex> lock(tasks_mutex_);
        tasks_by_time_[task->next_run].push_back(task);
        tasks_by_id_[task->id] = task;
    }
    cv_.notify_one();

    Logger::info("Scheduled once task " + std::to_string(task->id));
    return task->id;
}

TaskId TimeScheduler::scheduleInterval(const TaskCallback& callback,
                                        std::chrono::milliseconds interval,
                                        std::chrono::milliseconds initial_delay) {
    auto task = std::make_shared<Task>();
    task->id = generateTaskId();
    task->callback = callback;
    task->type = ScheduleType::INTERVAL;
    task->interval = interval;
    task->next_run = std::chrono::steady_clock::now() + initial_delay;

    {
        std::lock_guard<std::mutex> lock(tasks_mutex_);
        tasks_by_time_[task->next_run].push_back(task);
        tasks_by_id_[task->id] = task;
    }
    cv_.notify_one();

    Logger::info("Scheduled interval task " + std::to_string(task->id) +
                 " with interval " + std::to_string(interval.count()) + "ms");
    return task->id;
}

bool TimeScheduler::cancel(TaskId task_id) {
    std::lock_guard<std::mutex> lock(tasks_mutex_);
    auto it = tasks_by_id_.find(task_id);
    if (it != tasks_by_id_.end()) {
        it->second->cancelled = true;
        tasks_by_id_.erase(it);
        Logger::info("Cancelled task " + std::to_string(task_id));
        return true;
    }
    return false;
}

size_t TimeScheduler::activeTasks() const {
    std::lock_guard<std::mutex> lock(tasks_mutex_);
    return tasks_by_id_.size();
}

TaskId TimeScheduler::generateTaskId() {
    return next_task_id_++;
}

void TimeScheduler::schedulerThread() {
    while (!stopped_) {
        std::vector<TaskPtr> ready_tasks;
        std::chrono::steady_clock::time_point next_run_time;

        {
            std::unique_lock<std::mutex> lock(tasks_mutex_);

            // 查找下一个需要执行的任务
            while (!stopped_ && tasks_by_time_.empty()) {
                cv_.wait(lock);
            }
            if (stopped_) break;

            next_run_time = tasks_by_time_.begin()->first;
            auto now = std::chrono::steady_clock::now();

            if (next_run_time <= now) {
                // 执行到期的任务
                ready_tasks = std::move(tasks_by_time_.begin()->second);
                tasks_by_time_.erase(tasks_by_time_.begin());

                // 移除已取消的任务
                ready_tasks.erase(
                    std::remove_if(ready_tasks.begin(), ready_tasks.end(),
                        [](const TaskPtr& task) { return task->cancelled; }),
                    ready_tasks.end()
                );

                // 重新调度周期性任务
                for (auto& task : ready_tasks) {
                    if (task->type == ScheduleType::INTERVAL && !task->cancelled) {
                        task->next_run = now + task->interval;
                        tasks_by_time_[task->next_run].push_back(task);
                    } else {
                        // 一次性任务或已取消的任务从id映射中移除
                        tasks_by_id_.erase(task->id);
                    }
                }
            } else {
                // 等待到下一个任务执行时间
                cv_.wait_until(lock, next_run_time);
                continue;
            }
        }

        // 执行任务（不持有锁）
        for (auto& task : ready_tasks) {
            try {
                task->callback();
            } catch (const std::exception& e) {
                Logger::error("Exception in scheduled task " +
                             std::to_string(task->id) + ": " + e.what());
            } catch (...) {
                Logger::error("Unknown exception in scheduled task " +
                             std::to_string(task->id));
            }
        }
    }
}

} // namespace common
