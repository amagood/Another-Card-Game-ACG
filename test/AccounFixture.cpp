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
TEST_F(AccountFixture, Account_VERIFIED) {
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
TEST_F(AccountFixture, TEST_ACCOUNT_LOGINING) {
    std::string id("id");
    std::string password("123");
    Account a = Account(id, password);
    ASSERT_FALSE(a.isOnline());
    a.login();
    ASSERT_TRUE(a.isOnline());
    a.left();
    ASSERT_FALSE(a.isOnline());
}
/*
class Account{
public:
    Account(std::string &id, std::string &password);
    Account(nlohmann::json json);

    bool isSame(Account &another);
    bool isIDSame(std::string &other_id);
    bool verify(std::string &password);

    void modifyPassword(std::string &password);
    void modifyMoney(int money);
    nlohmann::json toJson();
    int getMoney();
    std::string getName();
    std::string getDeviceId();
    int getLadderPoint();
    uint32_t getUniqueNumber();
    U32vec getDeck ();
    U32vec getCards ();
    bool addCard(uint32_t);
    void setDeck(U32vec deck);
    void setCards(U32vec cards);

private:
    uint32_t user_id_ = 0; // TODO make it unique, readonly
    int money_ = 0;
    bool online = false;
    std::string id_;
    std::string password_;
    std::string device_id_;
    uint32_t win_ = 0;
    uint32_t lose_ = 0;


    int ladderPoint_ = 0;
    std::string ladderLevel = "copper";
    uint32_t ladder_win_;
    uint32_t ladder_lose_;
    // FIXME should add some interact with card and card list
    U32vec deck_card_list;
    U32vec card_list;
    // FIXME should add history

};
 */