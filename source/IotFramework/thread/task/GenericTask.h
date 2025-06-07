#pragma once

#include "Task.h"
#include <functional>
#include <utility>

namespace thread {

template <typename T>
class GenericTask : public ITask {
public:
    using Handler = std::function<void(const T&)>;

    GenericTask(T data, Handler handler) : mData(std::move(data)), mHandler(std::move(handler)) {}

    void execute() override {
        if (mHandler) mHandler(mData);
    }

private:
    T mData;
    Handler mHandler;
};

} // namespace thread
