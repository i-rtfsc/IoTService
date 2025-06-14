#pragma once

#include "IUserManager.h"
#include "PluginFactory.h"
#include "PluginRegistry.h"

#define USER_MANAGER_FACTORY_NAME "default"
#define USER_MANAGER_FACTORY_CLASS impl_user_default

IOT_USER_NS_BEGIN

/**
 * @brief 声明用户管理接口的插件工厂
 * @brief Declare the plugin factory for IUserManager interface
 *
 * 通过该宏声明插件工厂类，便于动态加载和实例化 IUserManager 实现类。
 * This macro declares the plugin factory class to facilitate dynamic loading and instantiation
 * of IUserManager implementations.
 */
DECLARE_FORCE_LINK_SYMBOL(USER_MANAGER_FACTORY_CLASS)
DECLARE_PLUGIN_FACTORY(IUserManager, UserManagerFactory, USER_MANAGER_FACTORY_CLASS);

IOT_USER_NS_END
