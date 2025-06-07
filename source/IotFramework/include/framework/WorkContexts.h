#pragma once

#include "common/NameSpaceDef.h"
#include <string>

IOT_FRAMEWORK_NS_BEGIN

struct CommandContext {
    std::string deviceId;
    std::string command;
    std::string userId;
    std::string token;
};

struct StatusReportContext {
    std::string deviceId;
    std::string status;
    std::string userId;
    std::string token;
};

struct HeartbeatContext {
    std::string deviceId;
    std::string userId;
    std::string token;
};

IOT_FRAMEWORK_NS_END