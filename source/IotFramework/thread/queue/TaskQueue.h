#pragma once

#include "../task/Task.h"
#include <condition_variable>
#include <mutex>
#include <queue>

namespace thread {

class TaskQueue {
public:
    void push(const TaskPtr& task) {
        {
            std::lock_guard<std::mutex> lock(mMutex);
            mQueue.push(task);
        }
        mCondition.notify_one();
    }

    TaskPtr pop() {
        std::unique_lock<std::mutex> lock(mMutex);
        mCondition.wait(lock, [this]() { return !mQueue.empty(); });
        auto task = mQueue.front();
        mQueue.pop();
        return task;
    }

    bool tryPop(TaskPtr& task) {
        std::lock_guard<std::mutex> lock(mMutex);
        if (mQueue.empty()) return false;
        task = mQueue.front();
        mQueue.pop();
        return true;
    }

private:
    std::queue<TaskPtr> mQueue;
    std::mutex mMutex;
    std::condition_variable mCondition;
};

} // namespace thread
