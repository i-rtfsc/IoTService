#pragma once

#include "IUserManager.h"
#include "PluginFactory.h"
#include "PluginRegistry.h"
#include "UserManagerFactory.h"

#include <iostream>

IOT_USER_NS_BEGIN

/**
 * @brief 默认用户管理器实现类
 * @brief Default implementation of IUserManager
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-15
 */
class MockUserManager : public IUserManager {
public:
    MockUserManager();
    ~MockUserManager() override;

    /**
     * @brief 验证用户合法性
     * @brief Validate user legitimacy
     *
     * mock 模式下，打印警告日志并直接通过验证。
     * In mock mode, logs a warning and directly passes validation.
     *
     * @param user 需要验证的用户对象 / The user object to validate
     * @return bool 返回验证结果 / Returns validation result
     */
    auto validateUser(const User& user) -> bool override;

private:
    static constexpr const char* kTAG = "MockUserManager";
};

IOT_USER_NS_END
