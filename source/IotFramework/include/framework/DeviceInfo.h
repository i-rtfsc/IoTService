#pragma once

#include "common/NameSpaceDef.h"
#include <chrono>
#include <string>

IOT_FRAMEWORK_NS_BEGIN

/**
 * @brief 设备状态枚举
 *
 * 设备状态包括：离线、在线、未知和错误。
 * @author Solo
 * @version 1.0
 */
enum class DeviceStatus {
    OFFLINE = 0,
    ONLINE = 1,
    UNKNOWN = 2,
    ERROR = 3
};

/**
 * @brief 设备信息结构体
 *
 * 包含设备状态、最后状态报告和最后心跳时间。
 * @author Solo
 * @version 1.0
 */
struct DeviceInfo {
    DeviceStatus status = DeviceStatus::UNKNOWN;
    std::string lastStatusReport;
    std::chrono::steady_clock::time_point lastHeartbeat;
};

IOT_FRAMEWORK_NS_END