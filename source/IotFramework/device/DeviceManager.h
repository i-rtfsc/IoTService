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

IOT_DEVICE_NS_BEGIN

/**
 * @brief 用于管理设备的注册、状态上报、心跳刷新及离线状态标记
 *
 * 该类通过分片哈希表（ShardedMap）高效地管理大量设备的信息，
 * 提供线程安全的注册、心跳更新、状态上报与查询接口。
 *
 * This class manages device registration, status reporting, heartbeat refreshing,
 * and offline marking. It uses a thread-safe sharded map to scale efficiently across devices.
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
class DeviceManager {
public:
    /**
     * @brief 构造函数
     *
     * 默认构造函数初始化分片设备表。
     */
    DeviceManager() = default;

    /**
     * @brief 注册设备
     *
     * 如果设备尚未存在于系统中，将其注册。
     *
     * @param deviceId 设备唯一标识符（Device ID）
     * @return true 表示注册成功；false 表示设备已存在
     *
     * Register a device into the system.
     * @return true if successfully registered; false if already exists
     */
    auto registerDevice(const std::string& deviceId) -> bool;

    /**
     * @brief 刷新设备心跳
     *
     * 更新设备最近一次心跳时间，表示设备仍然在线。
     *
     * @param deviceId 设备唯一标识符
     *
     * Refresh the heartbeat timestamp for the device.
     */
    void refreshDeviceHeartbeat(const std::string& deviceId);

    /**
     * @brief 标记设备为离线
     *
     * 将设备标记为离线状态。
     *
     * @param deviceId 设备唯一标识符
     *
     * Mark the device as offline.
     */
    void markDeviceOffline(const std::string& deviceId);

    /**
     * @brief 上报设备状态
     *
     * 将设备当前状态信息写入对应的 DeviceInfo 中。
     *
     * @param deviceId 设备唯一标识符
     * @param status 状态描述字符串
     *
     * Report the status message for the device.
     */
    void reportStatus(const std::string& deviceId, const std::string& status);

    /**
     * @brief 查询设备是否在线
     *
     * 判断当前设备是否处于在线状态（基于最近心跳时间或离线标记）。
     *
     * @param deviceId 设备唯一标识符
     * @return true 表示在线；false 表示离线或不存在
     *
     * Check whether the device is online.
     */
    auto isDeviceOnline(const std::string& deviceId) -> bool;

    /**
     * @brief 获取设备信息
     *
     * 查询设备详细信息并填充至输出参数。
     *
     * @param deviceId 设备唯一标识符
     * @param outInfo 输出参数，用于返回设备信息
     * @return true 表示查询成功；false 表示设备不存在
     *
     * Retrieve device info for a given device ID.
     */
    auto getDeviceInfo(const std::string& deviceId, DeviceInfo& outInfo) -> bool;

private:
    /**
     * @brief 日志 TAG 常量
     *
     * Logging tag for the DeviceManager module.
     */
    static constexpr const char* kTAG = "DeviceManager";

    /**
     * @brief 哈希分片数
     *
     * Shard count for the internal device map.
     * 越大越能提升并发读写性能，但占用更多内存。
     */
    static constexpr int SHARD_COUNT = 32;

    /**
     * @brief 设备信息表（支持并发访问）
     *
     * 通过自定义 ShardedMap 实现的线程安全设备映射表。
     * Key 为 deviceId，Value 为 DeviceInfo。
     *
     * Thread-safe map storing device information.
     */
    IOT_NS::ShardedMap<std::string, DeviceInfo, SHARD_COUNT> mDevices;
};

IOT_DEVICE_NS_END
