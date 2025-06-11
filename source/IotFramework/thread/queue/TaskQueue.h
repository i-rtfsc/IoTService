#pragma once

#include "common/NameSpaceDef.h"
#include "thread/task/Task.h"
#include <condition_variable>
#include <mutex>
#include <queue>

IOT_TASK_NS_BEGIN

/**
 * @brief 线程安全的任务队列，支持阻塞与非阻塞方式获取任务。
 *
 * TaskQueue 提供了线程安全的任务存取接口，内部通过互斥锁和条件变量
 * 实现生产者-消费者模型，支持任务的安全入队和出队操作。
 *
 * 主要功能包括：
 * - push: 将任务安全加入队列，并通知等待线程。
 * - pop: 阻塞等待直到有任务可用，然后弹出任务。
 * - tryPop: 非阻塞尝试弹出任务，若队列为空立即返回失败。
 *
 * 设计目标是确保多线程环境下任务的有序、安全执行。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
class TaskQueue {
public:
    /**
     * @brief 将任务加入队列，线程安全，操作完成后通知等待线程。
     * @param task 任务智能指针，表示待执行任务。
     */
    void push(const TaskPtr& task) {
        {
            std::lock_guard<std::mutex> lock(mMutex);
            mQueue.push(task);
        }
        mCondition.notify_one(); // 通知等待任务的线程
    }

    /**
     * @brief 阻塞等待任务可用并弹出队首任务。
     * @return 任务智能指针，调用者负责处理任务执行。
     */
    auto pop() -> TaskPtr {
        std::unique_lock<std::mutex> lock(mMutex);
        // 等待队列非空，防止虚假唤醒
        mCondition.wait(lock, [this]() { return !mQueue.empty(); });
        auto task = mQueue.front();
        mQueue.pop();
        return task;
    }

    /**
     * @brief 非阻塞尝试弹出任务。
     * @param task 任务智能指针的引用，用于存储弹出的任务。
     * @return 是否成功弹出任务，队列为空则返回 false。
     */
    auto tryPop(TaskPtr& task) -> bool {
        std::lock_guard<std::mutex> lock(mMutex);
        if (mQueue.empty()) return false;
        task = mQueue.front();
        mQueue.pop();
        return true;
    }

private:
    std::queue<TaskPtr> mQueue;         // 任务队列，先进先出
    std::mutex mMutex;                  // 互斥锁，保护任务队列的线程安全
    std::condition_variable mCondition; // 条件变量，用于线程间任务通知
};

IOT_TASK_NS_END
