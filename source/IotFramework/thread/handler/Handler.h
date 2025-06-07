#pragma once

#include "../task/Task.h"

namespace thread {

class IHandler {
public:
    virtual ~IHandler() = default;
    virtual void post(const TaskPtr& task) = 0;
};

} // namespace thread
