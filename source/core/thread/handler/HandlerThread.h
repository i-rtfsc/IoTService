#pragma once

#include "TaskHandler.h"
#include "common/NameSpaceDef.h"
#include "queue/TaskQueue.h"
#include "task/Task.h"
#include <atomic>
#include <memory>
#include <string>
#include <thread>

IOT_TASK_NS_BEGIN

/**
 * @brief 任务处理线程类
 *        Handler thread class for executing tasks asynchronously.
 *
 * 该类封装了一个独立线程，内部持有任务队列和任务处理器，
 * 支持启动和停止线程，持续从任务队列中取任务执行。
 *
 * This class encapsulates a dedicated thread that owns a task queue
 * and a task handler. It supports starting and stopping the thread,
 * continuously fetching and executing tasks from the queue.
 *
 * 设计用于实现异步任务处理模型，确保任务顺序执行，
 * 且线程安全，适合后台工作线程场景。
 *
 * Designed for asynchronous task processing model, ensuring tasks
 * are executed sequentially and thread-safe, suitable for background worker threads.
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
class HandlerThread {
public:
    /**
     * @brief 构造函数，初始化线程名称和运行状态
     *        Constructor initializes thread name and running flag.
     *
     * @param name 线程名称，默认 "Worker"
     *             Thread name, default is "Worker"
     */
    explicit HandlerThread(std::string name = "Worker")
        : mName(std::move(name)), isRunning(false) {}

    /**
     * @brief 析构函数，停止线程并释放资源
     *        Destructor stops the thread and releases resources.
     */
    ~HandlerThread() { stop(); }

    /**
     * @brief 启动处理线程，创建任务处理器并开启工作线程循环
     *        Start the handler thread, create task handler and run worker loop.
     */
    void start() {
        isRunning = true;
        mHandler = std::make_shared<TaskHandler>(mTaskQueue); // 创建任务处理器，绑定任务队列
        mWorker = std::thread(&HandlerThread::loop, this);    // 启动工作线程执行loop函数
    }

    /**
     * @brief 停止处理线程，设置运行标志为false，并通过推入空任务唤醒线程退出
     *        Stop the handler thread, set running flag to false, and push null task to exit loop.
     */
    void stop() {
        isRunning = false;
        mTaskQueue.push(nullptr); // 使用空任务唤醒线程以退出循环
        if (mWorker.joinable())   // 等待线程安全退出
            mWorker.join();
    }

    /**
     * @brief 获取当前线程对应的任务处理器接口
     *        Get the task handler interface associated with this thread.
     *
     * @return std::shared_ptr<IHandler> 任务处理接口智能指针
     *         Shared pointer to the task handler interface.
     */
    auto getHandler() const -> std::shared_ptr<IHandler> { return mHandler; }

private:
    /**
     * @brief 线程主循环，不断从任务队列获取任务并执行，遇到空任务退出
     *        Main loop of the thread, continuously pop tasks and execute them,
     *        exit loop when nullptr task is encountered.
     */
    void loop() {
        while (isRunning) {
            auto task = mTaskQueue.pop(); // 从队列获取任务，阻塞等待
            if (!task) break;             // nullptr表示退出信号，跳出循环
            task->execute();              // 执行任务
        }
    }

private:
    std::string mName;                     // 线程名称 Thread name
    std::atomic<bool> isRunning;           // 线程运行状态标志 Running state flag
    std::thread mWorker;                   // 工作线程 Worker thread
    TaskQueue mTaskQueue;                  // 任务队列，存储待处理任务 Task queue holding pending tasks
    std::shared_ptr<TaskHandler> mHandler; // 任务处理器，负责任务调度和执行 Task handler managing task dispatch and execution
};

IOT_TASK_NS_END
