//
// Created by jacky on 2019/4/6.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AccountSystem.h"

class AccountFixture : public ::testing::Test {
public:
    void SetUp() final{
    }
    void TearDown() final{

    }
};

TEST_F(AccountFixture, TEST_ACCOUNT_IS_SAME) {
    std::string id("id");
    std::string password("123");
    std::string password2("12352");
    Account a = Account(id, password);
    Account b = Account(id, password2);
    ASSERT_TRUE(a.is_same(b));
}

class AccountSystemFixture : public ::testing::Test {
public:
    AccountSystem account_system;
    void SetUp() final {
        account_system = AccountSystem();
    }
    void TearDown() final {

    }

};

TEST_F(AccountSystemFixture, TEST_CREATE_ACCOUNT) {
    std::string id("account");
    std::string keyword("keyword");
    ASSERT_TRUE(account_system.create_account(id, keyword));
    ASSERT_TRUE(account_system.exist(id));
}
TEST_F(AccountSystemFixture, TEST_NOT_TO_CREATE_ACCOUNT_TWICE) {
    std::string id("account");
    std::string keyword("keyword");
    ASSERT_TRUE(account_system.create_account(id, keyword));
    ASSERT_TRUE(account_system.exist(id));
    ASSERT_FALSE(account_system.create_account(id, keyword));
}

TEST_F(AccountSystemFixture, TEST_ACCOUNT_SYSTER_LOGIN) {
    std::string id("account");
    std::string keyword("keyword");
    ASSERT_TRUE(account_system.create_account(id, keyword));
    ASSERT_TRUE(account_system.login(id, keyword));
}


TEST_F(AccountSystemFixture, TEST_ACCOUNT_SYSTER_LOGIN_WRONG_INFO) {
    std::string id("account");
    std::string keyword("keyword");
    std::string wrong_keyword("wrong_keyword");
    std::string wrong_id("id_not_exist");

    ASSERT_TRUE(account_system.create_account(id, keyword));

    ASSERT_FALSE(account_system.login(id, wrong_keyword));
    ASSERT_FALSE(account_system.login(wrong_id, wrong_keyword));
    ASSERT_FALSE(account_system.login(wrong_id, keyword));
}