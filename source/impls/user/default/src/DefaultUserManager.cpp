#include "DefaultUserManager.h"
#include "PluginFactory.h"
#include "PluginRegistry.h"

IOT_USER_NS_BEGIN

/**
 * @brief 构造函数
 * @brief Constructor
 *
 * 输出构造日志。
 * Outputs constructor log.
 */
DefaultUserManager::DefaultUserManager() {
    std::cout << "[DefaultUserManager] Constructor\n";
}

/**
 * @brief 析构函数
 * @brief Destructor
 *
 * 输出析构日志。
 * Outputs destructor log.
 */
DefaultUserManager::~DefaultUserManager() {
    std::cout << "[DefaultUserManager] Destructor\n";
}

/**
 * @brief 验证用户合法性
 * @brief Validate user legitimacy
 *
 * 在模拟模式下，打印警告日志并直接通过验证。
 * In mock mode, logs a warning and directly passes validation.
 *
 * 在真实模式下，TODO: 实现真实验证逻辑，如调用 GRPC 服务或数据库接口。
 * In real mode, TODO: implement real validation logic such as calling GRPC service or database.
 *
 * @param user 需要验证的用户对象 / The user object to validate
 * @return bool 返回验证结果 / Returns validation result
 */
auto DefaultUserManager::validateUser(const User& user) -> bool {
#ifdef ENABLE_AUTH_MOCK
    std::cout << "[DefaultUserManager] Mock validation for user: " << user.userId << std::endl;
    return true;
#else
    // TODO: 这里实现真实的验证逻辑，比如调用 GRPC 服务或数据库接口
    return false;
#endif
}

IOT_USER_NS_END
