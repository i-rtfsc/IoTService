#include "DefaultUserManager.h"
#include "PluginFactory.h"
#include "PluginRegistry.h"

IOT_USER_NS_BEGIN

/**
 * @brief 注册默认用户管理器插件（Register the default user manager plugin）
 *
 * 该静态对象在模块加载阶段自动构造，
 * 将名为 "default"（由宏 `USER_MANAGER_DEFAULT` 定义）的插件注册到
 * `PluginFactory<IUserManager>` 中，并指定其构造函数为 `DefaultUserManager` 的共享指针。
 */
static PluginRegistrar<IUserManager> registerDefaultUserManager(
    USER_MANAGER_DEFAULT,
    []() { return std::make_shared<DefaultUserManager>(); });

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
 * TODO: 实现真实验证逻辑，如调用 GRPC 服务或数据库接口。
 * implement real validation logic such as calling GRPC service or database.
 *
 * @param user 需要验证的用户对象 / The user object to validate
 * @return bool 返回验证结果 / Returns validation result
 */
auto DefaultUserManager::validateUser(const User& user) -> bool {
    // TODO: 这里实现真实的验证逻辑，比如调用 GRPC 服务或数据库接口
    return false;
}

IOT_USER_NS_END
