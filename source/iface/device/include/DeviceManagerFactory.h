#pragma once

#include "IDeviceManager.h"
#include "PluginFactory.h"
#include "PluginRegistry.h"
#include "common/NameSpaceDef.h"

/// 默认设备管理器插件名称（Default implementation plugin name）
#define DEVICE_MANAGER_DEFAULT "default"

IOT_DEVICE_NS_BEGIN

/**
 * @class DeviceManagerFactory
 * @brief 设备管理器工厂类，用于获取 IDeviceManager 插件工厂实例。
 *
 * 提供对 `PluginFactory<IDeviceManager>` 的全局访问，支持设备管理器插件的注册与获取。
 * 用户可通过 `DeviceManagerFactory::instance()` 获取插件工厂，
 * 并根据插件名称创建对应的 `IDeviceManager` 实例。
 *
 * 使用示例（Typical usage）：
 * ```cpp
 * auto deviceManager = DeviceManagerFactory::instance().create("default");
 * ```
 *
 * @note 所有设备管理器插件应继承自 `IDeviceManager` 接口，并通过 `PluginRegistrar` 注册。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-15
 */
class DeviceManagerFactory {
public:
    /**
     * @brief 获取 IDeviceManager 插件工厂单例。
     *
     * 返回的是 `PluginFactory<IDeviceManager>` 的全局唯一实例。
     *
     * @return PluginFactory<IDeviceManager>& 插件工厂引用。
     */
    static PluginFactory<IDeviceManager>& instance() {
        return PluginFactory<IDeviceManager>::instance();
    }
};

IOT_DEVICE_NS_END
