#pragma once

#include <functional>
#include <chrono>
#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <map>

namespace common {

// 定时任务类型
enum class ScheduleType {
    ONCE,       // 执行一次
    INTERVAL,   // 间隔执行
    CRON        // Cron表达式（简化版，仅支持秒级）
};

// 定时任务描述符
using TaskId = uint64_t;
using TaskCallback = std::function<void()>;

class TimeScheduler {
public:
    struct Task {
        TaskId id;
        TaskCallback callback;
        ScheduleType type;
        std::chrono::steady_clock::time_point next_run;
        std::chrono::milliseconds interval;
        bool cancelled = false;
    };

    using TaskPtr = std::shared_ptr<Task>;

public:
    TimeScheduler();
    ~TimeScheduler();

    // 禁止拷贝和移动
    TimeScheduler(const TimeScheduler&) = delete;
    TimeScheduler& operator=(const TimeScheduler&) = delete;
    TimeScheduler(TimeScheduler&&) = delete;
    TimeScheduler& operator=(TimeScheduler&&) = delete;

    // 启动调度器
    void start();

    // 停止调度器
    void stop();

    // 添加一次性任务，delay后执行
    TaskId scheduleOnce(const TaskCallback& callback,
                       std::chrono::milliseconds delay);

    // 添加周期性任务，interval间隔执行
    TaskId scheduleInterval(const TaskCallback& callback,
                           std::chrono::milliseconds interval,
                           std::chrono::milliseconds initial_delay = std::chrono::milliseconds(0));

    // 取消任务
    bool cancel(TaskId task_id);

    // 获取活动任务数量
    size_t activeTasks() const;

    // 生成唯一任务ID
    TaskId generateTaskId();

private:
    // 调度器工作线程
    void schedulerThread();

private:
    std::thread scheduler_thread_;
    std::atomic<bool> running_;
    std::atomic<bool> stopped_;
    std::mutex tasks_mutex_;
    std::condition_variable cv_;
    std::map<std::chrono::steady_clock::time_point, std::vector<TaskPtr>> tasks_by_time_;
    std::map<TaskId, TaskPtr> tasks_by_id_;
    std::atomic<TaskId> next_task_id_;
};

} // namespace common
