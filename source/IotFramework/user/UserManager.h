#pragma once

#include "framework/User.h"
#include <string>

#include "common/NameSpaceDef.h"

IOT_FRAMEWORK_NS_BEGIN

/**
 * @brief 用户管理器类 - 负责用户验证和身份管理。
 * 跟外部gRPC服务交互，验证用户身份。
 *
 * @author Solo
 * @version 1.0
 */
class UserManager {
public:
    /**
     * @brief 验证用户身份
     * @param user 用户
     * @return 如果验证成功返回true，否则返回false
     */
    auto validateUser(const User& user) -> bool;

private:
    static constexpr const char* kTAG = "UserManager";
};

IOT_FRAMEWORK_NS_END