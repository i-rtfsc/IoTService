#pragma once

#include "../queue/TaskQueue.h"
#include "../task/Task.h"
#include "TaskHandler.h"
#include <atomic>
#include <memory>
#include <string>
#include <thread>

namespace thread {

class HandlerThread {
public:
    explicit HandlerThread(std::string name = "Worker") : mName(std::move(name)), isRunning(false) {}

    ~HandlerThread() { stop(); }

    void start() {
        isRunning = true;
        handler_ = std::make_shared<TaskHandler>(mTaskQueue);
        mWorker = std::thread(&HandlerThread::loop, this);
    }

    void stop() {
        isRunning = false;
        mTaskQueue.push(nullptr); // 使用空任务退出
        if (mWorker.joinable()) mWorker.join();
    }

    std::shared_ptr<IHandler> getHandler() const { return handler_; }

private:
    void loop() {
        while (isRunning) {
            auto task = mTaskQueue.pop();
            if (!task) break; // nullptr 退出线程
            task->execute();
        }
    }

    std::string mName;
    std::atomic<bool> isRunning;
    std::thread mWorker;
    TaskQueue mTaskQueue;
    std::shared_ptr<TaskHandler> handler_;
};

} // namespace thread
