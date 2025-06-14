/**
 * @brief Implementation of DefaultDeviceManager class
 * @brief DefaultDeviceManager 类的实现文件
 *
 * This file contains the logic for managing device lifecycle, status reporting, and online detection.
 * 本文件实现设备生命周期管理、状态上报以及在线状态检测等逻辑。
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-12
 */

#include "DefaultDeviceManager.h"

IOT_DEVICE_NS_BEGIN

/**
 * @brief Constructor
 * @brief 构造函数
 */
DefaultDeviceManager::DefaultDeviceManager() {
    std::cout << "[DefaultDeviceManager] Constructor\n";
}

/**
 * @brief Destructor
 * @brief 析构函数
 */
DefaultDeviceManager::~DefaultDeviceManager() {
    std::cout << "[DefaultDeviceManager] Destructor\n";
}

/**
 * @brief Initialize the manager
 * @brief 初始化管理器
 */
void DefaultDeviceManager::init() {
    std::cout << "[DefaultDeviceManager] init()\n";
}

/**
 * @brief Shutdown and cleanup
 * @brief 关闭并清理资源
 */
void DefaultDeviceManager::shutdown() {
    std::cout << "[DefaultDeviceManager] shutdown()\n";
}

/**
 * @brief Register a new device with given ID
 * @brief 根据设备 ID 注册新设备
 *
 * @param deviceId 设备唯一标识符
 * @return true 注册成功
 * @return false 设备已存在
 */
auto DefaultDeviceManager::registerDevice(const std::string& deviceId) -> bool {
    if (mDevices.contains(deviceId)) {
        return false;
    }

    DeviceInfo info;
    info.status = DeviceStatus::ONLINE;
    info.lastHeartbeat = std::chrono::steady_clock::now();
    info.lastStatusReport.clear();

    mDevices.insert(deviceId, std::move(info));

    std::cout << "[DefaultDeviceManager] Device registered: " << deviceId << std::endl;
    return true;
}

/**
 * @brief Refresh heartbeat time of a device
 * @brief 刷新设备的心跳时间
 *
 * @param deviceId 设备唯一标识符
 */
void DefaultDeviceManager::refreshDeviceHeartbeat(const std::string& deviceId) {
    auto opt = mDevices.get(deviceId);
    if (opt.has_value()) {
        auto& info = opt.value();
        info.lastHeartbeat = std::chrono::steady_clock::now();
        info.status = DeviceStatus::ONLINE;
        mDevices.insert(deviceId, info); // 更新信息
        std::cout << "[DefaultDeviceManager] Heartbeat refreshed for device: " << deviceId << std::endl;
    }
}

/**
 * @brief Mark a device as offline
 * @brief 将设备标记为离线状态
 *
 * @param deviceId 设备唯一标识符
 */
void DefaultDeviceManager::markDeviceOffline(const std::string& deviceId) {
    auto opt = mDevices.get(deviceId);
    if (opt.has_value()) {
        auto& info = opt.value();
        info.status = DeviceStatus::OFFLINE;
        mDevices.insert(deviceId, info); // 更新信息
        std::cout << "[DefaultDeviceManager] Device marked offline: " << deviceId << std::endl;
    }
}

/**
 * @brief Report status for a device
 * @brief 上报设备状态信息
 *
 * @param deviceId 设备唯一标识符
 * @param status 状态字符串（例如 JSON/XML）
 */
void DefaultDeviceManager::reportStatus(const std::string& deviceId, const std::string& status) {
    auto opt = mDevices.get(deviceId);
    if (opt.has_value()) {
        auto& info = opt.value();
        info.lastStatusReport = status;
        info.lastHeartbeat = std::chrono::steady_clock::now();
        info.status = DeviceStatus::ONLINE;
        mDevices.insert(deviceId, info); // 更新信息
        std::cout << "[DefaultDeviceManager] Status reported for device: " << deviceId << std::endl;
    }
}

/**
 * @brief Check if a device is online based on heartbeat timeout
 * @brief 根据心跳超时时间判断设备是否在线
 *
 * @param deviceId 设备唯一标识符
 * @return true 设备在线
 * @return false 设备离线或不存在
 */
auto DefaultDeviceManager::isDeviceOnline(const std::string& deviceId) -> bool {
    auto opt = mDevices.get(deviceId);
    if (!opt.has_value()) {
        return false;
    }

    auto& info = opt.value();
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - info.lastHeartbeat).count();

    if (duration > 30) {
        info.status = DeviceStatus::OFFLINE;
        mDevices.insert(deviceId, info); // 更新为离线状态
        return false;
    }

    return info.status == DeviceStatus::ONLINE;
}

/**
 * @brief Get full device info
 * @brief 获取完整的设备信息
 *
 * @param deviceId 设备唯一标识符
 * @param outInfo 输出的设备信息结构体
 * @return true 获取成功
 * @return false 设备不存在
 */
auto DefaultDeviceManager::getDeviceInfo(const std::string& deviceId, DeviceInfo& outInfo) -> bool {
    auto opt = mDevices.get(deviceId);
    if (!opt.has_value()) {
        return false;
    }

    outInfo = opt.value();
    return true;
}

IOT_DEVICE_NS_END
