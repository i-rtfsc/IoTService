#pragma once

/**
 * @brief 消息路由器头文件
 *        Header file for message routing logic
 *
 * 负责处理设备消息的核心路由逻辑，包括命令下发、状态上报、心跳处理等操作。
 * Responsible for routing device messages such as command dispatch, status reporting, and heartbeat handling.
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */

#include "DeviceManagerFactory.h"
#include "MessageTask.h"
#include "UserManagerFactory.h"
#include "handler/HandlerThread.h"
#include "task/GenericTask.h"

#include "common/NameSpaceDef.h"
#include <string>

IOT_NS_BEGIN

/**
 * @brief 消息路由器类
 *        Class for routing device-related messages
 *
 * 管理设备与用户之间的指令通信、状态同步、心跳检测和断连处理等。
 * Handles command routing, device status synchronization, heartbeat tracking, and disconnection management.
 */
class MessageRouter {
public:
    /**
     * @brief 构造函数，初始化用户管理器、设备管理器和消息线程。
     *        Constructor: initializes user/device managers and handler thread.
     */
    MessageRouter();

    /**
     * @brief 析构函数（使用默认实现）
     *        Destructor (default implementation)
     */
    ~MessageRouter() = default;

    /**
     * @brief 处理来自用户的指令消息
     *        Handle a command message sent from the user
     *
     * @param deviceId 目标设备ID / Target device ID
     * @param command 指令内容 / Command content
     * @param userId 用户ID / User ID
     * @param token 认证token / Authentication token
     * @return std::string 响应结果 / Response string
     */
    auto handleCommand(const std::string& deviceId, const std::string& command, const std::string& userId,
                       const std::string& token) -> std::string;

    /**
     * @brief 处理设备上报的状态信息
     *        Handle status report messages from device
     *
     * @param deviceId 设备ID / Device ID
     * @param status 状态内容 / Status string
     * @param userId 用户ID / User ID
     * @param token 认证token / Authentication token
     */
    void handleStatusReport(const std::string& deviceId, const std::string& status, const std::string& userId,
                            const std::string& token);

    /**
     * @brief 处理设备心跳包
     *        Handle device heartbeat signals
     *
     * @param deviceId 设备ID / Device ID
     * @param userId 用户ID / User ID
     * @param token 认证token / Authentication token
     * @return true 心跳有效 / Heartbeat accepted
     * @return false 心跳无效或失败 / Heartbeat rejected or failed
     */
    auto handleHeartbeat(const std::string& deviceId, const std::string& userId, const std::string& token) -> bool;

    /**
     * @brief 处理设备断开连接
     *        Handle device disconnection event
     *
     * @param deviceId 设备ID / Device ID
     */
    void handleDisconnect(const std::string& deviceId);

private:
    /**
     * @brief 将消息任务分发至处理线程
     *        Dispatch a message task to the processing thread
     *
     * @param task 消息任务对象 / Message task to dispatch
     */
    void dispatch(const MessageTask& task);

private:
    static constexpr const char* kTAG = "MessageRouter";                  // 日志标识 / Log tag identifier
    std::shared_ptr<IOT_USER_NS::IUserManager> mUserManagerFactory;       // 用户管理器工厂 / Factory for creating user managers
    std::shared_ptr<IOT_DEVICE_NS::IDeviceManager> mDeviceManagerFactory; // 设备管理器工厂 / Factory for creating device managers
    IOT_TASK_NS::HandlerThread mThead;                                    // 后台消息处理线程 / Background handler thread
};

IOT_NS_END
