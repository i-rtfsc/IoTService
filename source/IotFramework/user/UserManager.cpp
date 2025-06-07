#include "UserManager.h"

#include "utils/Log.h"

IOT_FRAMEWORK_NS_BEGIN

/**
 * @brief 用户管理器实现类 - 负责用户验证和身份管理。
 * 跟外部gRPC服务交互，验证用户身份。
 *
 * @author Solo
 * @version 1.0
 */
auto UserManager::validateUser(const User& user) -> bool {
#ifdef ENABLE_AUTH_MOCK
    LOGW(kTAG, "Mock token validation enabled. Skip real check for user: %s", user.userId.c_str());
    return true;
#else
    // TODO: 实际的验证逻辑，可能需要调用外部GRPC服务或数据库。
    return false;
#endif
}

IOT_FRAMEWORK_NS_END