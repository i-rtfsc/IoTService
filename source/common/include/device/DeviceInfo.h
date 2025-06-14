#pragma once

#include "common/NameSpaceDef.h"
#include <chrono>
#include <string>

IOT_NS_BEGIN

/**
 * @brief 设备状态枚举
 *        Enumeration representing the possible states of a device.
 *
 * 表示设备生命周期中的状态类型，包括离线、在线、未知和错误等。
 * Represents the lifecycle states of a device: offline, online, unknown, and error.
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
enum class DeviceStatus {
    OFFLINE = 0, // 设备离线 / Device is offline
    ONLINE = 1,  // 设备在线 / Device is online
    UNKNOWN = 2, // 状态未知 / Device state is unknown
    ERROR = 3    // 设备状态错误 / Device is in an error state
};

/**
 * @brief 设备信息结构体
 *        Structure holding the state and metadata of a device.
 *
 * 包含设备状态、最后一次状态上报信息和最后心跳时间，用于维护设备运行时状态。
 * Contains the device's current status, last reported status message,
 * and the most recent heartbeat timestamp.
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
struct DeviceInfo {
    DeviceStatus status = DeviceStatus::UNKNOWN;         // 当前设备状态 / Current device status
    std::string lastStatusReport;                        // 最近一次上报的状态信息 / Last reported custom status string
    std::chrono::steady_clock::time_point lastHeartbeat; // 最近一次心跳时间戳 / Timestamp of the last heartbeat
};

IOT_NS_END
