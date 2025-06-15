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
 * 负责实现用户验证的具体逻辑。
 * Implements the concrete logic for user validation.
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-12
 */
class DefaultUserManager : public IUserManager {
public:
    DefaultUserManager();
    ~DefaultUserManager() override;

    /**
     * @brief 验证用户合法性
     * @brief Validate the legitimacy of a user
     *
     * 根据业务规则判断传入的 User 对象是否合法。
     * Validates the given User object according to business rules.
     *
     * @param user 需要验证的用户对象 / The user object to validate
     * @return bool 返回验证结果 / Returns true if valid, false otherwise
     */
    auto validateUser(const User& user) -> bool override;

private:
    static constexpr const char* kTAG = "DefaultUserManager";
};

IOT_USER_NS_END
