#include "IUserManager.h"
#include "UserManagerFactory.h"
#include "common/NameSpaceDef.h"
#include "user/User.h"

#include <gtest/gtest.h>

using namespace std::chrono_literals;

class UserManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // 每个测试前清空状态（可选）
    }

    void TearDown() override {
        // 每个测试后清理（可选）
    }
    std::shared_ptr<IOT_USER_NS::IUserManager> manager =
        IOT_USER_NS::UserManagerFactory::instance().create(USER_MANAGER_DEFAULT);

    std::shared_ptr<IOT_USER_NS::IUserManager> mockManager =
        IOT_USER_NS::UserManagerFactory::instance().create(USER_MANAGER_MOCK);
};

TEST_F(UserManagerTest, ValidateMockUser_Success) {
    IOT_NS::User user = { "mock_user", "valid_token" };
    bool result = mockManager->validateUser(user);
    std::cout << "[ValidateMockUser_Success] result = " << result << std::endl;
    EXPECT_TRUE(result);
}

TEST_F(UserManagerTest, ValidateUser_Success) {
    IOT_NS::User user = { "mock_user", "valid_token" };
    bool result = manager->validateUser(user);
    std::cout << "[ValidateUser_Success] result = " << result << std::endl;
    EXPECT_TRUE(result);
}
