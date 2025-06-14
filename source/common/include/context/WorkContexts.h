#pragma once

#include "common/NameSpaceDef.h"
#include <string>

IOT_NS_BEGIN

/**
 * @brief 命令上下文结构体，封装设备命令相关信息。
 *        Structure representing the context for a device command, encapsulating command-related information.
 *
 * 用于传递设备 ID、命令内容及用户身份认证信息，方便执行设备命令。
 * Used to convey device ID, command content, and user authentication information for command execution.
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-07
 */
struct CommandContext {
    /**
     * @brief 设备唯一标识符
     *        Unique identifier of the device.
     */
    std::string deviceId;

    /**
     * @brief 设备命令字符串
     *        Command string to be sent to the device.
     */
    std::string command;

    /**
     * @brief 用户唯一标识符
     *        Unique identifier of the user.
     */
    std::string userId;

    /**
     * @brief 用户认证令牌
     *        Authentication token of the user.
     */
    std::string token;
};

/**
 * @brief 状态上报上下文结构体，封装设备状态上报相关信息。
 *        Structure representing the context for device status reporting, encapsulating status information.
 *
 * 用于传递设备 ID、状态字符串及用户身份认证信息，便于状态汇报处理。
 * Used to convey device ID, status string, and user authentication information for status reporting.
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-07
 */
struct StatusReportContext {
    /**
     * @brief 设备唯一标识符
     *        Unique identifier of the device.
     */
    std::string deviceId;

    /**
     * @brief 设备状态字符串
     *        Status string reported by the device.
     */
    std::string status;

    /**
     * @brief 用户唯一标识符
     *        Unique identifier of the user.
     */
    std::string userId;

    /**
     * @brief 用户认证令牌
     *        Authentication token of the user.
     */
    std::string token;
};

/**
 * @brief 心跳上下文结构体，封装设备心跳相关信息。
 *        Structure representing the context for a device heartbeat, encapsulating heartbeat-related information.
 *
 * 用于传递设备 ID 及用户身份认证信息，确保设备在线状态的维持。
 * Used to convey device ID and user authentication information to maintain device online status.
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-07
 */
struct HeartbeatContext {
    /**
     * @brief 设备唯一标识符
     *        Unique identifier of the device.
     */
    std::string deviceId;

    /**
     * @brief 用户唯一标识符
     *        Unique identifier of the user.
     */
    std::string userId;

    /**
     * @brief 用户认证令牌
     *        Authentication token of the user.
     */
    std::string token;
};

IOT_NS_END
