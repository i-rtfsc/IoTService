#pragma once

#include "common/NameSpaceDef.h"
#include <string>

IOT_NS_BEGIN

/**
 * @brief 用户信息结构体，包含用户 ID 和认证 token。
 *        Structure representing user information, including user ID and authentication token.
 *
 * 用于标识用户身份，并用于服务端进行认证处理。
 * Used to identify the user and perform server-side authentication.
 *
 * @author Solo
 * @version 1.1
 * @date 2025-06-07
 */
struct User {
    /**
     * @brief 用户唯一标识符
     *        Unique identifier for the user.
     */
    std::string userId;

    /**
     * @brief 用户认证令牌，用于身份验证
     *        Authentication token used for verifying user identity.
     */
    std::string token;
};

IOT_NS_END
