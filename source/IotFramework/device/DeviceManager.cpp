/**
 * @brief 设备管理器实现类，用于管理设备的注册、状态刷新、离线标记、状态上报等功能。
 *        Implementation of the DeviceManager class, which manages device registration,
 *        heartbeat refreshing, offline marking, and status reporting.
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */

#include "DeviceManager.h"

using namespace std::chrono;

IOT_DEVICE_NS_BEGIN

/**
 * @brief 注册设备。如果设备已存在则返回 false，否则插入设备信息并标记为在线。
 *        Register a device. If already registered, return false; otherwise, insert as online.
 *
 * @param deviceId 设备唯一 ID / Unique identifier of the device
 * @return true 注册成功 / Registration succeeded
 * @return false 设备已存在 / Device already exists
 */
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

/**
 * @brief 刷新设备心跳时间，并标记为在线。
 *        Refresh the heartbeat timestamp of the device and mark it as online.
 *
 * @param deviceId 设备唯一 ID / Unique identifier of the device
 */
void DeviceManager::refreshDeviceHeartbeat(const std::string& deviceId) {
    auto opt = mDevices.get(deviceId);
    if (opt.has_value()) {
        auto& info = opt.value();
        info.lastHeartbeat = steady_clock::now();
        info.status = DeviceStatus::ONLINE;
        mDevices.insert(deviceId, info); // 更新 / Update
        LOGD(kTAG, "Refreshed heartbeat for %s", deviceId.c_str());
    }
}

/**
 * @brief 将设备标记为离线状态。
 *        Mark the specified device as offline.
 *
 * @param deviceId 设备唯一 ID / Unique identifier of the device
 */
void DeviceManager::markDeviceOffline(const std::string& deviceId) {
    auto opt = mDevices.get(deviceId);
    if (opt.has_value()) {
        auto& info = opt.value();
        info.status = DeviceStatus::OFFLINE;
        mDevices.insert(deviceId, info); // 更新 / Update
        LOGW(kTAG, "Marked device offline %s", deviceId.c_str());
    }
}

/**
 * @brief 上报设备状态字符串，同时更新心跳时间与在线状态。
 *        Report a device's custom status, and update heartbeat and online status.
 *
 * @param deviceId 设备唯一 ID / Unique identifier of the device
 * @param status 状态字符串 / Custom status string reported by the device
 */
void DeviceManager::reportStatus(const std::string& deviceId, const std::string& status) {
    auto opt = mDevices.get(deviceId);
    if (opt.has_value()) {
        auto& info = opt.value();
        info.lastStatusReport = status;
        info.lastHeartbeat = steady_clock::now();
        info.status = DeviceStatus::ONLINE;
        mDevices.insert(deviceId, info); // 更新 / Update
        LOGI(kTAG, "Device %s reported status: %s", deviceId.c_str(), status.c_str());
    }
}

/**
 * @brief 判断设备是否在线（30 秒无心跳视为离线）。
 *        Check whether the device is online (offline if no heartbeat within 30 seconds).
 *
 * @param deviceId 设备唯一 ID / Unique identifier of the device
 * @return true 在线 / Online
 * @return false 离线或不存在 / Offline or not found
 */
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
        mDevices.insert(deviceId, info); // 更新 / Update
        return false;
    }

    return info.status == DeviceStatus::ONLINE;
}

/**
 * @brief 获取设备信息。
 *        Retrieve detailed device info by ID.
 *
 * @param deviceId 设备唯一 ID / Unique identifier of the device
 * @param outInfo 输出设备信息 / Output parameter to receive device info
 * @return true 获取成功 / Retrieved successfully
 * @return false 设备不存在 / Device not found
 */
auto DeviceManager::getDeviceInfo(const std::string& deviceId, DeviceInfo& outInfo) -> bool {
    auto opt = mDevices.get(deviceId);
    if (!opt.has_value()) {
        return false;
    }

    outInfo = opt.value();
    return true;
}

IOT_DEVICE_NS_END
