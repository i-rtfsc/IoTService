#pragma once

#include "common/NameSpaceDef.h"
#include <memory>

IOT_TASK_NS_BEGIN

/**
 * @brief 任务接口类，定义了所有任务必须实现的执行接口。
 *
 * ITask 是任务的抽象基类，所有具体任务类需继承自该接口并实现 execute() 方法。
 * 通过该接口，任务可以被统一管理和调度，支持多态调用。
 *
 * 该接口设计用于多线程环境中的任务调度框架，保证任务具有统一的执行行为。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
class ITask {
public:
    /**
     * @brief 虚析构函数，确保派生类对象通过基类指针删除时资源正确释放。
     */
    virtual ~ITask() = default;

    /**
     * @brief 纯虚函数，执行任务的具体逻辑由派生类实现。
     */
    virtual void execute() = 0;
};

/**
 * @typedef TaskPtr
 * @brief 任务智能指针类型，使用 std::shared_ptr 管理任务生命周期。
 */
using TaskPtr = std::shared_ptr<ITask>;

IOT_TASK_NS_END
