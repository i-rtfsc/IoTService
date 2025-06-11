#pragma once

#include "framework/User.h"
#include <string>

#include "common/NameSpaceDef.h"

IOT_USER_NS_BEGIN

/**
 * @brief 用户管理类，负责用户相关的业务逻辑处理。
 *
 * UserManager 提供用户验证功能，判断传入的 User 对象是否合法。
 * 该类可扩展为包含更多用户管理相关的接口和功能。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
class UserManager {
public:
    /**
     * @brief 验证用户合法性。
     *
     * 根据业务规则对传入的 User 对象进行验证，判断其是否合法有效。
     *
     * @param user 需要验证的用户对象。
     * @return bool 返回 true 表示用户验证通过，false 表示验证失败。
     */
    auto validateUser(const User& user) -> bool;

private:
    static constexpr const char* kTAG = "UserManager"; // 日志标签，标识日志来源于 UserManager 类。
};

IOT_USER_NS_END
