#include "MessageRouter.h"

#include <gtest/gtest.h>
#include <memory>
#include <string>

class MessageRouterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 可选：提前注册设备或用户等初始化逻辑
    }

    void TearDown() override {
        // 可选：清理资源
    }

    IOT_NS::MessageRouter router;
};

// 测试用例：处理用户指令
TEST_F(MessageRouterTest, HandleCommand_ShouldReturnExpectedResponse) {
    std::string deviceId = "device123";
    std::string command = "open";
    std::string userId = "user456";
    std::string token = "valid-token";

    std::string result = router.handleCommand(deviceId, command, userId, token);

    // 示例断言，可根据实际实现调整
    EXPECT_FALSE(result.empty());
}

// 测试用例：设备状态上报
TEST_F(MessageRouterTest, HandleStatusReport_ShouldNotThrow) {
    std::string deviceId = "device001";
    std::string status = "online";
    std::string userId = "user001";
    std::string token = "token001";

    // 不抛异常即为通过
    EXPECT_NO_THROW(router.handleStatusReport(deviceId, status, userId, token));
}

// 测试用例：设备心跳处理
TEST_F(MessageRouterTest, HandleHeartbeat_ShouldReturnTrueIfValid) {
    std::string deviceId = "device002";
    std::string userId = "user002";
    std::string token = "token002";

    bool success = router.handleHeartbeat(deviceId, userId, token);

    // 断言心跳结果
    EXPECT_TRUE(success); // 或 EXPECT_FALSE()，看默认行为
}

// 测试用例：设备断连
TEST_F(MessageRouterTest, HandleDisconnect_ShouldNotThrow) {
    std::string deviceId = "device003";

    EXPECT_NO_THROW(router.handleDisconnect(deviceId));
}
