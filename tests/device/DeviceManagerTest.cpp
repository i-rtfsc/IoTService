#include "DeviceManagerFactory.h"
#include "common/NameSpaceDef.h"
#include "device/DeviceInfo.h"

#include <chrono>
#include <gtest/gtest.h>
#include <thread>

using namespace std::chrono_literals;

class DeviceManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 每个测试前清空状态（可选）
    }

    void TearDown() override {
        // 每个测试后清理（可选）
    }

    std::shared_ptr<IOT_DEVICE_NS::IDeviceManager> manager =
        IOT_DEVICE_NS::DeviceManagerFactory::instance().create(DEVICE_MANAGER_DEFAULT);
};

TEST_F(DeviceManagerTest, RegisterDevice_Success) {
    std::string deviceId = "device001";
    EXPECT_TRUE(manager->registerDevice(deviceId));

    IOT_NS::DeviceInfo info;
    EXPECT_TRUE(manager->getDeviceInfo(deviceId, info));
    EXPECT_EQ(info.status, IOT_NS::DeviceStatus::ONLINE);
}

TEST_F(DeviceManagerTest, RegisterDevice_Duplicate) {
    std::string deviceId = "device002";
    EXPECT_TRUE(manager->registerDevice(deviceId));
    EXPECT_FALSE(manager->registerDevice(deviceId)); // 再次注册应失败
}

TEST_F(DeviceManagerTest, RefreshHeartbeat) {
    std::string deviceId = "device003";
    EXPECT_TRUE(manager->registerDevice(deviceId));

    std::this_thread::sleep_for(50ms);
    manager->refreshDeviceHeartbeat(deviceId);

    IOT_NS::DeviceInfo info;
    EXPECT_TRUE(manager->getDeviceInfo(deviceId, info));
    EXPECT_EQ(info.status, IOT_NS::DeviceStatus::ONLINE);
}

TEST_F(DeviceManagerTest, MarkDeviceOffline) {
    std::string deviceId = "device004";
    EXPECT_TRUE(manager->registerDevice(deviceId));
    manager->markDeviceOffline(deviceId);

    IOT_NS::DeviceInfo info;
    EXPECT_TRUE(manager->getDeviceInfo(deviceId, info));
    EXPECT_EQ(info.status, IOT_NS::DeviceStatus::OFFLINE);
}

TEST_F(DeviceManagerTest, ReportStatus) {
    std::string deviceId = "device005";
    std::string report = "temperature=28C";
    EXPECT_TRUE(manager->registerDevice(deviceId));

    manager->reportStatus(deviceId, report);

    IOT_NS::DeviceInfo info;
    EXPECT_TRUE(manager->getDeviceInfo(deviceId, info));
    EXPECT_EQ(info.lastStatusReport, report);
}

TEST_F(DeviceManagerTest, IsDeviceOnline_BasedOnHeartbeat) {
    std::string deviceId = "device006";
    EXPECT_TRUE(manager->registerDevice(deviceId));
    EXPECT_TRUE(manager->isDeviceOnline(deviceId));

    // 模拟心跳超时逻辑（如果你有实现的话，这里测试失效）
}

TEST_F(DeviceManagerTest, GetDeviceInfo_NotExist) {
    IOT_NS::DeviceInfo dummy;
    EXPECT_FALSE(manager->getDeviceInfo("not_exist_device", dummy));
}
