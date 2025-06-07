#include "framework/MessageRouter.h"
#include "utils/Log.h"

IOT_FRAMEWORK_NS_BEGIN

MessageRouter::MessageRouter() {
    mThead.start(); // 启动内部处理线程
    mUserManager = std::make_unique<UserManager>();
    mDeviceManager = std::make_unique<DeviceManager>();
}

std::string MessageRouter::handleCommand(const std::string& deviceId, const std::string& command,
                                         const std::string& userId, const std::string& token) {
    dispatch(MessageTask { MessageTask::Type::Command, deviceId, command, userId, token });
    return "Command accepted";
}

void MessageRouter::handleStatusReport(const std::string& deviceId, const std::string& status,
                                       const std::string& userId, const std::string& token) {
    dispatch(MessageTask { MessageTask::Type::StatusReport, deviceId, status, userId, token });
}

bool MessageRouter::handleHeartbeat(const std::string& deviceId, const std::string& userId, const std::string& token) {
    dispatch(MessageTask { MessageTask::Type::Heartbeat, deviceId,
                           "", // 无 payload
                           userId, token });
    return true;
}

void MessageRouter::handleDisconnect(const std::string& deviceId) {
    dispatch(MessageTask { MessageTask::Type::Disconnect, deviceId, "", "", "" });
}

void MessageRouter::dispatch(const MessageTask& task) {
    auto handler = mThead.getHandler();
    if (!handler) {
        LOGE(kTAG, "No handler thread available.");
        return;
    }

    handler->post(std::make_shared<thread::GenericTask<MessageTask>>(task, [this](const MessageTask& t) {
        User user { t.userId, t.token };
        if (!mUserManager->validateUser(user)) {
            LOGW(kTAG, "Token validation failed for user %s", t.userId.c_str());
            return;
        }

        switch (t.type) {
        case MessageTask::Type::Command:
            if (!mDeviceManager->isDeviceOnline(t.deviceId)) {
                mDeviceManager->registerDevice(t.deviceId);
            }
            LOGI(kTAG, "Command '%s' sent to device %s", t.commandOrStatus.c_str(), t.deviceId.c_str());
            break;

        case MessageTask::Type::StatusReport:
            mDeviceManager->reportStatus(t.deviceId, t.commandOrStatus);
            break;

        case MessageTask::Type::Heartbeat:
            LOGD(kTAG, "Heartbeat from device %s", t.deviceId.c_str());
            mDeviceManager->refreshDeviceHeartbeat(t.deviceId);
            break;

        case MessageTask::Type::Disconnect:
            LOGI(kTAG, "Device %s disconnected", t.deviceId.c_str());
            mDeviceManager->markDeviceOffline(t.deviceId);
            break;
        }
    }));
}

IOT_FRAMEWORK_NS_END