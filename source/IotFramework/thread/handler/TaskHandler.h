#pragma once

#include "../queue/TaskQueue.h"
#include "Handler.h"

namespace thread {

class TaskHandler : public IHandler {
public:
    explicit TaskHandler(TaskQueue& queue) : mTaskQueue(queue) {}

    void post(const TaskPtr& task) override { mTaskQueue.push(task); }

private:
    TaskQueue& mTaskQueue;
};

} // namespace thread
