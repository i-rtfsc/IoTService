// message_task.h
#pragma once

#include "common/NameSpaceDef.h"

IOT_FRAMEWORK_NS_BEGIN

/**
 * @brief 表示消息任务的数据结构，供线程调度处理使用
 */
struct MessageTask {
    enum class Type {
        Command,
        StatusReport,
        Heartbeat,
        Disconnect
    };

    Type type;
    std::string deviceId;
    std::string commandOrStatus;
    std::string userId;
    std::string token;
};

IOT_FRAMEWORK_NS_END