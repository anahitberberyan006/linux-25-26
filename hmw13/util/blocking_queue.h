#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue {
public:
    explicit BlockingQueue(size_t capacity)
            : capacity_(capacity) {}

    // push (blocking)
    void push(const T& value) {
        std::unique_lock<std::mutex> lock(mutex_);

        not_full_.wait(lock, [this]() {
            return queue_.size() < capacity_;
        });

        queue_.push(value);

        not_empty_.notify_one();
    }

    // pop (blocking)
    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);

        not_empty_.wait(lock, [this]() {
            return !queue_.empty();
        });

        T value = queue_.front();
        queue_.pop();

        not_full_.notify_one();

        return value;
    }

    // try_pop (non-blocking)
    bool try_pop(T& value) {
        std::lock_guard<std::mutex> lock(mutex_);

        if (queue_.empty())
            return false;

        value = queue_.front();
        queue_.pop();

        not_full_.notify_one();

        return true;
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    bool full() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size() == capacity_;
    }

private:
    std::queue<T> queue_;
    size_t capacity_;

    mutable std::mutex mutex_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
};