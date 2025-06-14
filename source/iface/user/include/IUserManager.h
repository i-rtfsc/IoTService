#pragma once

#include "user/User.h"

IOT_USER_NS_BEGIN

/**
 * @brief Interface for user management
 * @brief 用户管理接口
 *
 * Provides abstract operations related to user management, such as user validation.
 * 提供与用户管理相关的抽象操作，如用户验证。
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-12
 */
class IUserManager {
public:
    virtual ~IUserManager() = default;

    /**
     * @brief Validate the legality of a user
     * @brief 验证用户合法性
     *
     * Validates the given User object according to business rules to determine if it is valid and legitimate.
     * 根据业务规则对传入的 User 对象进行验证，判断其是否合法有效。
     *
     * @param user The User object to validate / 需要验证的用户对象
     * @return bool Returns true if the user is valid, false otherwise / 返回 true 表示用户验证通过，false 表示验证失败
     */
    virtual auto validateUser(const User& user) -> bool = 0;
};

IOT_USER_NS_END
