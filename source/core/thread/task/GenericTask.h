#pragma once

#include "Task.h"
#include "common/NameSpaceDef.h"
#include <functional>
#include <utility>

IOT_TASK_NS_BEGIN

/**
 * @brief 泛型任务模板类，用于封装带有参数的任务执行逻辑。
 *
 * GenericTask 是 ITask 的模板派生类，支持传入任意类型的数据和对应的处理函数，
 * 通过调用 execute() 执行该处理函数，并传入封装的数据。
 *
 * 该设计实现了任务执行的高度灵活性和通用性，适用于各种类型的数据驱动任务。
 *
 * @tparam T 任务处理所需数据类型。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
template <typename T>
class GenericTask : public ITask {
public:
    /// 处理函数类型，接收一个常量引用类型的参数 T，无返回值。
    using Handler = std::function<void(const T&)>;

    /**
     * @brief 构造函数，初始化任务数据和处理函数。
     * @param data 任务处理所需的数据，使用移动语义优化性能。
     * @param handler 具体处理该数据的函数对象。
     */
    GenericTask(T data, Handler handler)
        : mData(std::move(data)), mHandler(std::move(handler)) {}

    /**
     * @brief 重写基类的 execute 方法，执行封装的处理函数，传入任务数据。
     */
    void execute() override {
        if (mHandler) mHandler(mData);
    }

private:
    T mData;          // 任务数据，类型由模板参数指定。
    Handler mHandler; // 任务处理函数，用于执行具体业务逻辑。
};

IOT_TASK_NS_END
