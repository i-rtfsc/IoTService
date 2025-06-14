#pragma once

#include "IDeviceManager.h"
#include "PluginFactory.h"
#include "PluginRegistry.h"
#include "common/NameSpaceDef.h"

/// @brief Default factory name for device manager plugin.
/// @brief 设备管理器插件的默认工厂名称
#define DEVICE_MANAGER_FACTORY_NAME "default"

/// @brief Class name of the default device manager implementation.
/// @brief 默认设备管理器实现类的名称
#define DEVICE_MANAGER_FACTORY_CLASS impl_device_default

IOT_DEVICE_NS_BEGIN

/**
 * @brief Ensure the symbol DEVICE_MANAGER_FACTORY_CLASS is linked into final binary.
 * @brief 强制链接 DEVICE_MANAGER_FACTORY_CLASS 符号到最终可执行文件中
 *
 * This macro ensures that the implementation class symbol is preserved
 * during linking, which is essential for plugin systems using dynamic registration.
 * 该宏确保在链接时保留实现类符号，适用于基于插件的动态注册系统。
 */
DECLARE_FORCE_LINK_SYMBOL(DEVICE_MANAGER_FACTORY_CLASS)

/**
 * @brief Declare a plugin factory for IDeviceManager.
 * @brief 为 IDeviceManager 声明插件工厂
 *
 * Registers the class DEVICE_MANAGER_FACTORY_CLASS as the default factory class
 * under the plugin category IDeviceManager.
 * 将 DEVICE_MANAGER_FACTORY_CLASS 注册为 IDeviceManager 的默认工厂实现，
 * 供插件系统按名称加载。
 */
DECLARE_PLUGIN_FACTORY(IDeviceManager, DeviceManagerFactory, DEVICE_MANAGER_FACTORY_CLASS);

IOT_DEVICE_NS_END
