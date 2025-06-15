#pragma once

#include "IUserManager.h"
#include "PluginFactory.h"
#include "PluginRegistry.h"

/// 默认用户管理器插件名称（Default implementation plugin name）
#define USER_MANAGER_DEFAULT "default"

/// Mock 用户管理器插件名称（Mock implementation plugin name for testing）
#define USER_MANAGER_MOCK "mock"

IOT_USER_NS_BEGIN

/**
 * @class UserManagerFactory
 * @brief 用户管理器工厂类，用于获取 IUserManager 插件工厂实例。
 *
 * 提供对 `PluginFactory<IUserManager>` 的全局访问，支持用户管理器插件的注册与获取。
 * 使用者可通过 `UserManagerFactory::instance()` 获取插件工厂，
 * 并使用注册名称创建对应的 IUserManager 实例。
 *
 * Typical usage 示例：
 * ```cpp
 * auto userManager = UserManagerFactory::instance().create("default");
 * ```
 *
 * @note 所有用户管理器插件应继承自 IUserManager 接口，并通过 PluginRegistrar 注册。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-15
 */
class UserManagerFactory {
public:
    /**
     * @brief 获取 IUserManager 插件工厂单例。
     *
     * 返回的是 `PluginFactory<IUserManager>` 的全局唯一实例。
     *
     * @return PluginFactory<IUserManager>& 插件工厂引用。
     */
    static PluginFactory<IUserManager>& instance() {
        return PluginFactory<IUserManager>::instance();
    }
};

IOT_USER_NS_END
