#include "MockUserManager.h"
#include "PluginFactory.h"
#include "PluginRegistry.h"

IOT_USER_NS_BEGIN

/**
 * @brief 注册Mock用户管理器插件（Register the mock user manager plugin）
 *
 * 该静态对象在模块加载阶段自动构造，
 * 将名为 "mock"（由宏 `USER_MANAGER_MOCK` 定义）的插件注册到
 * `PluginFactory<IUserManager>` 中，并指定其构造函数为 `MockUserManager` 的共享指针。
 */
static PluginRegistrar<IUserManager> registerMockUserManager(
    USER_MANAGER_MOCK,
    []() { return std::make_shared<MockUserManager>(); });

/**
 * @brief 构造函数
 * @brief Constructor
 *
 * 输出构造日志。
 * Outputs constructor log.
 */
MockUserManager::MockUserManager() {
    std::cout << "[MockUserManager] Constructor\n";
}

/**
 * @brief 析构函数
 * @brief Destructor
 *
 * 输出析构日志。
 * Outputs destructor log.
 */
MockUserManager::~MockUserManager() {
    std::cout << "[MockUserManager] Destructor\n";
}

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
auto MockUserManager::validateUser(const User& user) -> bool {
    return true;
}

IOT_USER_NS_END
