#include "UserManager.h"
#include "utils/Log.h"

IOT_USER_NS_BEGIN

/**
 * @brief 验证用户是否合法。
 *
 * 根据编译时宏 ENABLE_AUTH_MOCK 判断是否启用模拟验证：
 * - 如果启用模拟验证，打印警告日志，直接返回 true，跳过实际验证。
 * - 否则，执行实际的用户验证逻辑（此处为 TODO，未来可能调用 GRPC 服务或数据库校验）。
 *
 * @param user 待验证的用户对象。
 * @return bool 返回 true 表示用户验证通过，false 表示验证失败。
 *
 * @note 该函数依赖预编译宏 ENABLE_AUTH_MOCK 来控制验证行为，方便测试环境绕过验证。
 *
 * @author Solo
 * @version 1.0
 * @date 2025-06-07
 */
auto UserManager::validateUser(const User& user) -> bool {
#ifdef ENABLE_AUTH_MOCK
    // 模拟模式下，打印警告日志并直接通过验证
    LOGW(kTAG, "Mock token validation enabled. Skip real check for user: %s", user.userId.c_str());
    return true;
#else
    // TODO: 这里实现真实的验证逻辑，比如调用 GRPC 服务或数据库接口
    return false;
#endif
}

IOT_USER_NS_END
