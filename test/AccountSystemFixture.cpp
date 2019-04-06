//
// Created by jacky on 2019/4/6.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "AccountSystem.h"


class AccountSystemFixture : public ::testing::Test {
public:
    AccountSystem accountSystem;
    virtual void SetUp(){
        accountSystem = AccountSystem();
//        accountSystem = new AccountSystem();
    }
    virtual void TearDown(){

    }
};

TEST_F(AccountSystemFixture, TEST_CREATE_ACCOUNT) {
    std::string account("account");
    std::string keyword("keyword");
    ASSERT_TRUE(accountSystem.createAccount(account, keyword));
    ASSERT_TRUE(accountSystem.isAccountExist(account));

}