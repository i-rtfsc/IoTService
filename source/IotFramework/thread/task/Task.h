#pragma once

#include <memory>

namespace thread {

class ITask {
public:
    virtual ~ITask() = default;
    virtual void execute() = 0;
};

using TaskPtr = std::shared_ptr<ITask>;

} // namespace thread
