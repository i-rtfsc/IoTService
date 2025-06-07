#pragma once

#include "common/NameSpaceDef.h"
#include <string>

IOT_FRAMEWORK_NS_BEGIN

/**
 * @brief 设备信息结构体
 *
 * 包含设备状态、最后状态报告和最后心跳时间。
 * @author Solo
 * @version 1.0
 */
struct User {
    std::string userId;
    std::string token;
};

IOT_FRAMEWORK_NS_END