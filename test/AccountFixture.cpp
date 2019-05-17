//
// Created by jacky on 2019/5/18.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Account.h"

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
    ASSERT_TRUE(a.isSame(b));
}
TEST_F(AccountFixture, TEST_Account_VERIFIED) {
    std::string id("id");
    std::string password("123");
    std::string password2("12352");
    Account a = Account(id, password);
    ASSERT_TRUE(a.verify(password));
    ASSERT_FALSE(a.verify(password2));
    a.modifyPassword(password2);
    ASSERT_TRUE(a.verify(password2));
    ASSERT_FALSE(a.verify(password));
}

TEST_F(AccountFixture, TEST_ACCOUNT_IS_ID_SAME) {
    std::string id("id");
    std::string password("123");
    Account a = Account(id, password);
    ASSERT_EQ(a.getName(), "id");
    ASSERT_NE(a.getName(), "ID");
}

TEST_F(AccountFixture, TEST_ACCOUNT_MODIFY_PASSWORD) {
    std::string id("id");
    std::string password("123");
    Account a = Account(id, password);
    ASSERT_TRUE(a.verify("123"));
    a.modifyPassword("basdf");
    ASSERT_TRUE(a.verify("basdf"));
    ASSERT_FALSE(a.verify("123"));
}
TEST_F(AccountFixture, TEST_ACCOUNT_GET_MONEY) {
    std::string id("id");
    std::string password("123");
    Account a = Account(id, password);
    ASSERT_EQ(0, a.getMoney());
}

TEST_F(AccountFixture, TEST_ACCOUNT_MODIFY_MONEY) {
    std::string id("id");
    std::string password("123");
    Account a = Account(id, password);
    ASSERT_EQ(0, a.getMoney());
    a.modifyMoney(100);
    ASSERT_EQ(100, a.getMoney());
    a.modifyMoney(-50);
    ASSERT_EQ(50, a.getMoney());

}
TEST_F(AccountFixture, TEST_ACCOUNT_MONEY_NOT_LESS_THAN_ZERO) {
    std::string id("id");
    std::string password("123");
    Account a = Account(id, password);
    ASSERT_EQ(0, a.getMoney());
    a.modifyMoney(100);
    ASSERT_EQ(100, a.getMoney());
    // less than zero
    a.modifyMoney(-500);
    ASSERT_EQ(0, a.getMoney());
    a.modifyMoney(-500);
    ASSERT_EQ(0, a.getMoney());
}
TEST_F(AccountFixture, TEST_ACCOUNT_LOGIN_LEFT_ONLINE) {
    std::string id("id");
    std::string password("123");
    Account a = Account(id, password);
    ASSERT_FALSE(a.isOnline());
    a.login();
    ASSERT_TRUE(a.isOnline());
    a.left();
    ASSERT_FALSE(a.isOnline());
}
TEST_F(AccountFixture, TEST_ACCOUNT_CARD_TEST) {
    std::string id("id");
    std::string password("123");
    Account a = Account(id, password);
    U32vec card = a.getCards();
    EXPECT_TRUE(card.empty());
    a.addCard(23); // add a card number is 23
    card = a.getCards();
    EXPECT_FALSE(card.empty());
    EXPECT_EQ(std::find(card.begin(), card.end(), 22), card.end());
    EXPECT_NE(std::find(card.begin(), card.end(), 23), card.end());
    a.setCards({1, 2, 3, 5});
    card = a.getCards();
    EXPECT_NE(std::find(card.begin(), card.end(), 1), card.end());
    // old one is not exist anymore
    EXPECT_EQ(std::find(card.begin(), card.end(), 22), card.end());
}