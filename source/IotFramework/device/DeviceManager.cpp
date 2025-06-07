#include "DeviceManager.h"

using namespace std::chrono;

IOT_FRAMEWORK_NS_BEGIN

DeviceManager::DeviceManager() {}

auto DeviceManager::registerDevice(const std::string& deviceId) -> bool {
    if (mDevices.contains(deviceId)) {
        return false;
    }

    DeviceInfo info;
    info.status = DeviceStatus::ONLINE;
    info.lastHeartbeat = steady_clock::now();
    info.lastStatusReport.clear();

    mDevices.insert(deviceId, std::move(info));

    LOGI(kTAG, "Registered device %s", deviceId.c_str());
    return true;
}

void DeviceManager::refreshDeviceHeartbeat(const std::string& deviceId) {
    auto opt = mDevices.get(deviceId);
    if (opt.has_value()) {
        auto& info = opt.value();
        info.lastHeartbeat = steady_clock::now();
        info.status = DeviceStatus::ONLINE;
        mDevices.insert(deviceId, info); // 更新
        LOGD(kTAG, "Refreshed heartbeat for %s", deviceId.c_str());
    }
}

void DeviceManager::markDeviceOffline(const std::string& deviceId) {
    auto opt = mDevices.get(deviceId);
    if (opt.has_value()) {
        auto& info = opt.value();
        info.status = DeviceStatus::OFFLINE;
        mDevices.insert(deviceId, info); // 更新
        LOGW(kTAG, "Marked device offline %s", deviceId.c_str());
    }
}

void DeviceManager::reportStatus(const std::string& deviceId, const std::string& status) {
    auto opt = mDevices.get(deviceId);
    if (opt.has_value()) {
        auto& info = opt.value();
        info.lastStatusReport = status;
        info.lastHeartbeat = steady_clock::now();
        info.status = DeviceStatus::ONLINE;
        mDevices.insert(deviceId, info); // 更新
        LOGI(kTAG, "Device %s reported status: %s", deviceId.c_str(), status.c_str());
    }
}

auto DeviceManager::isDeviceOnline(const std::string& deviceId) -> bool {
    auto opt = mDevices.get(deviceId);
    if (!opt.has_value()) {
        return false;
    }

    auto& info = opt.value();
    auto now = steady_clock::now();
    auto duration = duration_cast<seconds>(now - info.lastHeartbeat).count();

    if (duration > 30) {
        info.status = DeviceStatus::OFFLINE;
        mDevices.insert(deviceId, info); // 更新
        return false;
    }

    return info.status == DeviceStatus::ONLINE;
}

auto DeviceManager::getDeviceInfo(const std::string& deviceId, DeviceInfo& outInfo) -> bool {
    auto opt = mDevices.get(deviceId);
    if (!opt.has_value()) {
        return false;
    }

    outInfo = opt.value();
    return true;
}

IOT_FRAMEWORK_NS_END