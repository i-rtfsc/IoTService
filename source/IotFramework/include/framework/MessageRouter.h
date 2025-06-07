#pragma once

#include "../../device/DeviceManager.h"
#include "../../message/MessageTask.h"
#include "../../thread/handler/HandlerThread.h"
#include "../../thread/task/GenericTask.h"
#include "../../user/UserManager.h"

#include "common/NameSpaceDef.h"
#include <string>

IOT_FRAMEWORK_NS_BEGIN

/**
 * @brief 消息路由器类 - 负责处理设备命令、状态上报与心跳包。
 * @author
 * @version 1.0
 */
class MessageRouter {
public:
    MessageRouter();

    ~MessageRouter() = default;

    /**
     * @brief 处理来自客户端的命令请求
     * @param deviceId 设备 ID
     * @param command  设备命令
     * @param userId   用户 ID
     * @param token    用户身份令牌
     * @return 返回命令接收确认
     */
    std::string handleCommand(const std::string& deviceId, const std::string& command, const std::string& userId,
                              const std::string& token);

    /**
     * @brief 处理设备状态上报
     */
    void handleStatusReport(const std::string& deviceId, const std::string& status, const std::string& userId,
                            const std::string& token);

    /**
     * @brief 处理设备心跳包
     * @return 是否验证成功
     */
    bool handleHeartbeat(const std::string& deviceId, const std::string& userId, const std::string& token);

    /**
     * @brief 处理设备断开连接事件
     * @param deviceId 设备 ID
     */
    void handleDisconnect(const std::string& deviceId);

private:
    void dispatch(const MessageTask& task);

private:
    static constexpr const char* kTAG = "MessageRouter";
    std::unique_ptr<UserManager> mUserManager;
    std::unique_ptr<DeviceManager> mDeviceManager;
    thread::HandlerThread mThead;
};

IOT_FRAMEWORK_NS_END