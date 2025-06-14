#pragma once

#include "common/NameSpaceDef.h"
#include "device/DeviceInfo.h"
#include <iostream>

IOT_DEVICE_NS_BEGIN

/**
 * @brief Interface for managing device registration, heartbeat, status reporting, and querying.
 * @brief 接口定义：用于管理设备的注册、心跳、状态上报和信息查询
 *
 * All device-related operations such as registration, heartbeat refresh,
 * status update, and device info retrieval should be implemented via this interface
 * to ensure centralized and consistent management.
 * 所有设备的注册、心跳上报、状态同步、信息获取等操作，都应通过该接口实现，
 * 以确保系统中对设备的统一管理和状态一致性。
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-12
 */
class IDeviceManager {
public:
    virtual ~IDeviceManager() = default;

    /**
     * @brief Initialize the device manager.
     * @brief 初始化设备管理器
     *
     * This method should be called at system startup to prepare internal states.
     * 应在系统启动时优先调用，用于分配资源和初始化状态。
     */
    virtual void init() = 0;

    /**
     * @brief Shut down the device manager.
     * @brief 停止设备管理器
     *
     * Should be called before system shutdown to release resources safely.
     * 应在系统退出或服务关闭前调用，以释放相关资源。
     */
    virtual void shutdown() = 0;

    /**
     * @brief Register a device by its ID.
     * @brief 注册设备
     *
     * @param deviceId Unique identifier of the device. 设备唯一标识符
     * @return true if registration succeeds, false otherwise.
     *         注册成功返回 true，否则返回 false。
     */
    virtual auto registerDevice(const std::string& deviceId) -> bool = 0;

    /**
     * @brief Refresh the heartbeat of a device.
     * @brief 刷新设备心跳
     *
     * @param deviceId Unique identifier of the device. 设备唯一标识符
     *
     * This keeps the device marked as online.
     * 用于维持设备在线状态。
     */
    virtual void refreshDeviceHeartbeat(const std::string& deviceId) = 0;

    /**
     * @brief Mark a device as offline.
     * @brief 标记设备为离线
     *
     * @param deviceId Unique identifier of the device. 设备唯一标识符
     */
    virtual void markDeviceOffline(const std::string& deviceId) = 0;

    /**
     * @brief Report current status of the device.
     * @brief 上报设备状态
     *
     * @param deviceId Unique identifier of the device. 设备唯一标识符
     * @param status Status string, could be JSON/XML/etc. 状态信息（如 JSON、XML）
     */
    virtual void reportStatus(const std::string& deviceId, const std::string& status) = 0;

    /**
     * @brief Check if a device is currently online.
     * @brief 判断设备是否在线
     *
     * @param deviceId Unique identifier of the device. 设备唯一标识符
     * @return true if the device is online, false otherwise.
     *         在线返回 true，否则返回 false。
     */
    virtual auto isDeviceOnline(const std::string& deviceId) -> bool = 0;

    /**
     * @brief Retrieve detailed information of a device.
     * @brief 获取设备信息
     *
     * @param deviceId Unique identifier of the device. 设备唯一标识符
     * @param outInfo Output reference to receive device info. 输出的设备信息结构体
     * @return true if retrieval succeeds, false otherwise.
     *         成功返回 true，否则返回 false。
     */
    virtual auto getDeviceInfo(const std::string& deviceId, DeviceInfo& outInfo) -> bool = 0;
};

IOT_DEVICE_NS_END
