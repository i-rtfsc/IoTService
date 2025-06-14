#pragma once

#include "common/NameSpaceDef.h"
#include <iostream>

IOT_NS_BEGIN

/**
 * @brief 消息任务结构体，表示不同类型的设备消息任务。
 *        Structure representing a message task with various device-related message types.
 *
 * 用于统一封装设备的命令、状态上报、心跳及断开连接消息，方便任务调度和处理。
 * Used to uniformly encapsulate device commands, status reports, heartbeats, and disconnect messages for task scheduling and processing.
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
struct MessageTask {
    /**
     * @brief 消息任务类型枚举，区分不同消息类别。
     *        Enum class defining the type of message task.
     */
    enum class Type {
        /**
         * @brief 设备命令类型
         *        Device command type.
         */
        Command,

        /**
         * @brief 设备状态上报类型
         *        Device status report type.
         */
        StatusReport,

        /**
         * @brief 设备心跳类型，用于维持在线状态
         *        Device heartbeat type, used to maintain online status.
         */
        Heartbeat,

        /**
         * @brief 设备断开连接类型
         *        Device disconnect type.
         */
        Disconnect
    };

    /**
     * @brief 消息任务类型
     *        The type of the message task.
     */
    Type type;

    /**
     * @brief 设备唯一标识符
     *        Unique identifier of the device.
     */
    std::string deviceId;

    /**
     * @brief 命令或状态字符串，根据消息类型含义不同
     *        Command or status string; meaning varies based on the message type.
     */
    std::string commandOrStatus;

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
