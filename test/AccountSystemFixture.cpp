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
TEST_F(AccountFixture, Account_VERIFIED) {
    std::string id("id");
    std::string password("123");
    std::string password2("12352");
    Account a = Account(id, password);
    ASSERT_TRUE(a.verify(password));
    ASSERT_FALSE(a.verify(password2));
    a.modify_password(password2);
    ASSERT_TRUE(a.verify(password2));
    ASSERT_FALSE(a.verify(password));
}

class AccountSystemFixture : public ::testing::Test {
public:
    AccountSystem account_system;
    std::string exist_id = "already_in_id";
    std::string exist_pwd = "already_in_pwd";
    void SetUp() final {
        account_system = AccountSystem();

        account_system.create_account(exist_id, exist_pwd);
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

TEST_F(AccountSystemFixture, TEST_MODIFIY_PASSWORD) {
    std::string new_pwd("new_pwd");
    // wrong old password
    ASSERT_FALSE(account_system.modify_password(exist_id, new_pwd, exist_pwd));
    // true old password
    ASSERT_TRUE(account_system.modify_password(exist_id, exist_pwd, new_pwd));

    ASSERT_FALSE(account_system.login(exist_id, exist_pwd));

    ASSERT_TRUE(account_system.login(exist_id, new_pwd));
}


TEST_F(AccountSystemFixture, TEST_ACCOUNT_MONEY) {
    int money = 100;
    int money2 = 33;
    account_system.modify_money(exist_id, money);
    EXPECT_EQ(account_system.get_money(exist_id), money);
    account_system.modify_money(exist_id, money);
    EXPECT_EQ(account_system.get_money(exist_id), 2 * money);
    account_system.modify_money(exist_id, -money);
    EXPECT_EQ(account_system.get_money(exist_id), money);
    account_system.modify_money(exist_id, money2);
    EXPECT_EQ(account_system.get_money(exist_id), money+money2);
}

