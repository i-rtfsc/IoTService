#pragma once

#include "common/NameSpaceDef.h"
#include "task/Task.h"

IOT_TASK_NS_BEGIN

/**
 * @brief 任务处理接口类
 *        Interface class for task handling.
 *
 * 定义了异步任务处理的统一接口，所有具体的任务处理器
 * 需实现该接口的post方法，将任务投递到相应的执行队列或线程中。
 *
 * Defines a unified interface for asynchronous task handling.
 * Any concrete task handler should implement the `post` method
 * to enqueue tasks to the appropriate execution queue or thread.
 *
 * 设计为纯虚类，保证子类必须实现post方法，实现多态。
 * Designed as an abstract class with a pure virtual `post` method,
 * ensuring subclasses provide their own implementation for polymorphism.
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
class IHandler {
public:
    virtual ~IHandler() = default; // 虚析构函数，确保子类析构正确 Virtual destructor to ensure proper cleanup of derived classes

    /**
     * @brief 投递任务接口，将任务提交给处理器执行
     *        Post a task to the handler for execution.
     *
     * @param task 需要执行的任务指针，智能指针类型保证生命周期管理
     *             The task pointer to be executed, managed by smart pointer for automatic lifecycle management.
     */
    virtual void post(const TaskPtr& task) = 0;
};

IOT_TASK_NS_END
