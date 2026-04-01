#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

class ThreadPool {
public:
    ThreadPool()
            : stop_(false)
    {
        size_t threads_count = std::thread::hardware_concurrency();
        if (threads_count == 0) threads_count = 4;

        for (size_t i = 0; i < threads_count; ++i) {
            workers_.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(mutex_);

                        condition_.wait(lock, [this]() {
                            return stop_ || !tasks_.empty();
                        });

                        if (stop_ && tasks_.empty())
                            return;

                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }

                    task(); // execute
                }
            });
        }
    }

    // enqueue
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();

        {
            std::lock_guard<std::mutex> lock(mutex_);

            if (stop_)
                throw std::runtime_error("enqueue on stopped ThreadPool");

            tasks_.emplace([task]() { (*task)(); });
        }

        condition_.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_ = true;
        }

        condition_.notify_all();

        for (std::thread &worker : workers_) {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex mutex_;
    std::condition_variable condition_;
    bool stop_;
};#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>

class ThreadPool {
public:
    ThreadPool()
            : stop_(false)
    {
        size_t threads_count = std::thread::hardware_concurrency();
        if (threads_count == 0) threads_count = 4;

        for (size_t i = 0; i < threads_count; ++i) {
            workers_.emplace_back([this]() {
                while (true) {
                    std::function<void()> task;

                    {
                        std::unique_lock<std::mutex> lock(mutex_);

                        condition_.wait(lock, [this]() {
                            return stop_ || !tasks_.empty();
                        });

                        if (stop_ && tasks_.empty())
                            return;

                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }

                    task(); // execute
                }
            });
        }
    }

    // enqueue
    template<typename F, typename... Args>
    auto enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
    {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();

        {
            std::lock_guard<std::mutex> lock(mutex_);

            if (stop_)
                throw std::runtime_error("enqueue on stopped ThreadPool");

            tasks_.emplace([task]() { (*task)(); });
        }

        condition_.notify_one();
        return res;
    }

    ~ThreadPool() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_ = true;
        }

        condition_.notify_all();

        for (std::thread &worker : workers_) {
            worker.join();
        }
    }

private:
    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> tasks_;

    std::mutex mutex_;
    std::condition_variable condition_;
    bool stop_;
};