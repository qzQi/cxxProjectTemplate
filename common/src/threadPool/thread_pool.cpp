#include "thread_pool.h"
#include "logger/logger.h"
#include <stdexcept>

namespace common {

ThreadPool::ThreadPool(size_t num_threads) : stop_(false), active_workers_(0) {
    for (size_t i = 0; i < num_threads; ++i) {
        workers_.emplace_back([this] { worker(); });
    }
    Logger::info("ThreadPool initialized with " + std::to_string(num_threads) + " threads");
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }
    condition_.notify_all();

    for (auto& worker : workers_) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    Logger::info("ThreadPool destroyed");
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            condition_.wait(lock, [this] {
                return stop_ || !tasks_.empty();
            });

            if (stop_ && tasks_.empty()) {
                return;
            }

            task = std::move(tasks_.front());
            tasks_.pop();
        }

        ++active_workers_;
        try {
            task();
        } catch (const std::exception& e) {
            Logger::error("Exception in ThreadPool worker: " + std::string(e.what()));
        } catch (...) {
            Logger::error("Unknown exception in ThreadPool worker");
        }
        --active_workers_;

        finished_.notify_one();
    }
}

void ThreadPool::wait() {
    std::unique_lock<std::mutex> lock(finished_mutex_);
    finished_.wait(lock, [this] {
        std::unique_lock<std::mutex> queue_lock(queue_mutex_);
        return tasks_.empty() && active_workers_ == 0;
    });
}

size_t ThreadPool::size() const {
    return workers_.size();
}

size_t ThreadPool::pendingTasks() const {
    std::unique_lock<std::mutex> lock(queue_mutex_);
    return tasks_.size();
}

} // namespace common
