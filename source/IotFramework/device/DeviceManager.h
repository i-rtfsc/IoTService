#pragma once

#include <chrono>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/NameSpaceDef.h"
#include "common/ShardedMap.h"
#include "framework/DeviceInfo.h"
#include "utils/Log.h"

IOT_FRAMEWORK_NS_BEGIN

class DeviceManager {
public:
    DeviceManager();

    auto registerDevice(const std::string& deviceId) -> bool;
    void refreshDeviceHeartbeat(const std::string& deviceId);
    void markDeviceOffline(const std::string& deviceId);
    void reportStatus(const std::string& deviceId, const std::string& status);
    auto isDeviceOnline(const std::string& deviceId) -> bool;
    auto getDeviceInfo(const std::string& deviceId, DeviceInfo& outInfo) -> bool;

private:
    static constexpr const char* kTAG = "DeviceManager";
    static constexpr int SHARD_COUNT = 32;
    IOT_COMMON_NS::ShardedMap<std::string, DeviceInfo, SHARD_COUNT> mDevices;
};

IOT_FRAMEWORK_NS_END