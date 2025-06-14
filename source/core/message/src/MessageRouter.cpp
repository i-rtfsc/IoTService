#include "MessageRouter.h"

#include "user/User.h"

#include <iostream>

IOT_NS_BEGIN

/**
 * @brief 消息路由器类，实现设备消息的分发与处理逻辑
 *        MessageRouter class that implements dispatch and handling of device messages.
 *
 * 负责接收不同类型的设备消息（命令、状态上报、心跳、断开连接），
 * 并将消息封装成任务派发给后台线程处理，确保异步和线程安全。
 * Responsible for receiving different types of device messages (command, status report, heartbeat, disconnect),
 * packaging them into tasks, and dispatching to a background thread for asynchronous and thread-safe processing.
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
MessageRouter::MessageRouter() {
    mThead.start(); // 启动内部处理线程，保证消息异步处理
    mDeviceManagerFactory = IOT_DEVICE_NS::DeviceManagerFactory::instance().create(DEVICE_MANAGER_FACTORY_NAME);
    mUserManagerFactory = IOT_USER_NS::UserManagerFactory::instance().create(USER_MANAGER_FACTORY_NAME);
}

/**
 * @brief 处理设备命令消息，封装任务后派发
 *        Handle device command message, wrap into task and dispatch.
 *
 * @param deviceId 设备唯一标识符
 * @param command  命令内容字符串
 * @param userId   用户唯一标识符
 * @param token    用户认证令牌
 * @return std::string 返回处理结果字符串，固定为"Command accepted"
 */
auto MessageRouter::handleCommand(const std::string& deviceId, const std::string& command, const std::string& userId,
                                  const std::string& token) -> std::string {
    dispatch(MessageTask { MessageTask::Type::Command, deviceId, command, userId, token });
    return "Command accepted";
}

/**
 * @brief 处理设备状态上报消息，封装任务后派发
 *        Handle device status report message, wrap into task and dispatch.
 *
 * @param deviceId 设备唯一标识符
 * @param status   状态内容字符串
 * @param userId   用户唯一标识符
 * @param token    用户认证令牌
 */
void MessageRouter::handleStatusReport(const std::string& deviceId, const std::string& status,
                                       const std::string& userId, const std::string& token) {
    dispatch(MessageTask { MessageTask::Type::StatusReport, deviceId, status, userId, token });
}

/**
 * @brief 处理设备心跳消息，封装任务后派发
 *        Handle device heartbeat message, wrap into task and dispatch.
 *
 * @param deviceId 设备唯一标识符
 * @param userId   用户唯一标识符
 * @param token    用户认证令牌
 * @return bool   始终返回 true，表示心跳接收成功
 */
auto MessageRouter::handleHeartbeat(const std::string& deviceId, const std::string& userId,
                                    const std::string& token) -> bool {
    dispatch(MessageTask { MessageTask::Type::Heartbeat, deviceId,
                           "", // 心跳无附加负载
                           userId, token });
    return true;
}

/**
 * @brief 处理设备断开连接消息，封装任务后派发
 *        Handle device disconnect message, wrap into task and dispatch.
 *
 * @param deviceId 设备唯一标识符
 */
void MessageRouter::handleDisconnect(const std::string& deviceId) {
    dispatch(MessageTask { MessageTask::Type::Disconnect, deviceId, "", "", "" });
}

/**
 * @brief 消息任务派发函数，将任务交给后台线程处理
 *        Dispatch message task to background thread for processing.
 *
 * 先获取线程处理器，若不可用则打印错误日志。
 * 根据任务类型调用不同的设备管理操作，
 * 并进行用户身份验证，验证失败则打印警告并中止处理。
 *
 * @param task 待处理的消息任务
 */
void MessageRouter::dispatch(const MessageTask& task) {
    auto handler = mThead.getHandler();
    if (!handler) {
        std::cerr << "No handler thread available." << std::endl;
        return;
    }

    // 创建异步任务，在线程中执行具体业务逻辑
    handler->post(std::make_shared<IOT_TASK_NS::GenericTask<MessageTask>>(task, [this](const MessageTask& t) {
        //        User user { t.userId, t.token };
        //        if (!mUserManagerFactory->validateUser(user)) { // 验证用户Token
        //            std::cout << "Token validation failed for user " << t.userId << std::endl;
        //            return;
        //        }

        // 根据任务类型执行不同操作
        switch (t.type) {
        case MessageTask::Type::Command:
            // 若设备不在线则注册设备
            std::cout << "Processing command for device " << t.deviceId << ": " << t.commandOrStatus << std::endl;
            if (!mDeviceManagerFactory->isDeviceOnline(t.deviceId)) {
                mDeviceManagerFactory->registerDevice(t.deviceId);
            }
            std::cout << "Command '" << t.commandOrStatus << "' sent to device " << t.deviceId << std::endl;
            break;

        case MessageTask::Type::StatusReport:
            //            mDeviceManagerFactory->reportStatus(t.deviceId, t.commandOrStatus);
            break;

        case MessageTask::Type::Heartbeat:
            std::cout << "Heartbeat received from device " << t.deviceId << std::endl;
            //            mDeviceManagerFactory->refreshDeviceHeartbeat(t.deviceId);
            break;

        case MessageTask::Type::Disconnect:
            std::cout << "Device " << t.deviceId << " disconnected." << std::endl;
            //            mDeviceManagerFactory->markDeviceOffline(t.deviceId);
            break;
        }
    }));
}

IOT_NS_END
