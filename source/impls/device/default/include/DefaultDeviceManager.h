#pragma once

#include "DeviceManagerFactory.h"
#include "IDeviceManager.h"
#include "PluginFactory.h"
#include "PluginRegistry.h"
#include "common/NameSpaceDef.h"
#include "common/ShardedMap.h"

#include <iostream>

IOT_DEVICE_NS_BEGIN

/**
 * @brief Default implementation of IDeviceManager interface.
 * @brief 设备管理接口 IDeviceManager 的默认实现类
 *
 * Provides basic registration, heartbeat, status reporting and querying functionalities.
 * 提供设备注册、心跳维护、状态上报和信息查询等基础功能。
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-12
 */
class DefaultDeviceManager : public IDeviceManager {
public:
    /**
     * @brief Constructor
     * @brief 构造函数
     */
    DefaultDeviceManager();

    /**
     * @brief Destructor
     * @brief 析构函数
     */
    ~DefaultDeviceManager() override;

    /**
     * @brief Initialize internal resources.
     * @brief 初始化内部资源
     */
    void init() override;

    /**
     * @brief Cleanup resources before shutdown.
     * @brief 释放资源，准备关闭
     */
    void shutdown() override;

    /**
     * @brief Register a device by its ID.
     * @brief 根据设备 ID 注册设备
     *
     * @param deviceId Unique identifier of the device
     * @return Whether registration is successful
     * @return 注册是否成功
     */
    auto registerDevice(const std::string& deviceId) -> bool override;

    /**
     * @brief Update device's heartbeat timestamp to maintain online state.
     * @brief 刷新设备心跳时间以保持在线状态
     *
     * @param deviceId Unique identifier of the device
     */
    void refreshDeviceHeartbeat(const std::string& deviceId) override;

    /**
     * @brief Mark a device as offline.
     * @brief 将设备标记为离线
     *
     * @param deviceId Unique identifier of the device
     */
    void markDeviceOffline(const std::string& deviceId) override;

    /**
     * @brief Report current status of a device.
     * @brief 上报设备当前状态
     *
     * @param deviceId Unique identifier of the device
     * @param status Status string (e.g., JSON/XML format)
     * @param status 状态字符串（如 JSON/XML 格式）
     */
    void reportStatus(const std::string& deviceId, const std::string& status) override;

    /**
     * @brief Check if the device is currently online.
     * @brief 查询设备是否处于在线状态
     *
     * @param deviceId Unique identifier of the device
     * @return true if device is online, false otherwise
     */
    auto isDeviceOnline(const std::string& deviceId) -> bool override;

    /**
     * @brief Get detailed information about the device.
     * @brief 获取设备的详细信息
     *
     * @param deviceId Unique identifier of the device
     * @param outInfo Output parameter to store device info
     * @return Whether retrieval was successful
     * @return 是否成功获取信息
     */
    auto getDeviceInfo(const std::string& deviceId, DeviceInfo& outInfo) -> bool override;

private:
    /// @brief Log tag used for debugging and logging
    /// @brief 用于日志打印的标签
    static constexpr const char* kTAG = "DeviceManager";

    /// @brief Number of shards used in internal device map for concurrency
    /// @brief 内部设备映射的分片数量，用于并发优化
    static constexpr int SHARD_COUNT = 32;

    /// @brief Sharded map storing device information keyed by device ID
    /// @brief 基于设备 ID 存储设备信息的分片哈希表
    IOT_NS::ShardedMap<std::string, DeviceInfo, SHARD_COUNT> mDevices;
};

IOT_DEVICE_NS_END
