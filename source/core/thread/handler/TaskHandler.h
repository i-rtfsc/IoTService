#pragma once

#include "Handler.h"
#include "common/NameSpaceDef.h"
#include "queue/TaskQueue.h"

IOT_TASK_NS_BEGIN

/**
 * @brief 任务处理类，实现 IHandler 接口，负责将任务投递到任务队列中。
 *
 * TaskHandler 是任务执行机制中的核心组件，负责将外部提交的任务放入线程安全的任务队列，
 * 供工作线程（HandlerThread）异步处理。通过依赖注入方式获取 TaskQueue 的引用，
 * 保证任务的有序和线程安全。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
class TaskHandler : public IHandler {
public:
    /**
     * @brief 构造函数，绑定外部任务队列引用。
     * @param queue 任务队列的引用，用于存放和管理待执行任务。
     */
    explicit TaskHandler(TaskQueue& queue)
        : mTaskQueue(queue) {}

    /**
     * @brief 将任务投递到任务队列中，等待被工作线程处理。
     * @param task 需要执行的任务智能指针。
     */
    void post(const TaskPtr& task) override { mTaskQueue.push(task); }

private:
    TaskQueue& mTaskQueue; ///< 任务队列引用，负责任务的存储和管理
};

IOT_TASK_NS_END
