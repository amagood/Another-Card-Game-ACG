//
// Created by jacky on 2019/4/6.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H

#include <cstdint>

#include <vector>
#include <string>
#include <queue>
#include <mutex>

#include <nlohmann/json.hpp>

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
    std::string getName(){return name_;}
    int getLadderPoint(){return ladderPoint_;}
    uint32_t getUniqueNumber() { return user_id_;}
    std::vector<uint32_t> getDeck (){
        return deck_card_list;
    };
private:
    uint32_t user_id_ = 0; // TODO make it unique, readonly
    int money_ = 0;
    std::string name_;

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
    std::vector<uint32_t > deck_card_list;
    std::vector<uint32_t> card_list;
    // FIXME should add history

};

class AccountSystem {
public:

    AccountSystem();
    bool createAccount(std::string &id, std::string &password);
    bool exist(std::string &account_name);
    bool login(std::string &account_name, std::string &password);
    bool logout(uint32_t user_id_){return true;};
    bool modifyPassword(std::string &id, std::string &ori_password, std::string &new_password);
    void modifyMoney(std::string &id, int money);
    void modifyMoney(uint32_t user_id_, int money);
    int getMoney(std::string &id);
    void loadAccounts();
    void saveAccount(int u_num, nlohmann::json j);
    void saveAccounts();
    void getAccountInfo(int u_num){};
    void getCards(int){};
    void drawCard(int){};
    void modifyCards(uint32_t user_id_, std::vector<uint32_t> cards, std::vector<uint32_t> deck){};
    std::string getAccountName(uint32_t user_id_){return "";};
    std::string getUserName(uint32_t userId){
        for (Account &account: account_vector) {
            if (account.getUniqueNumber() == userId) {
                return account.getName();
            }
        }
    }
    std::vector<uint32_t> getDeck(uint32_t userId) {
        for (Account &account: account_vector) {
            if (account.getUniqueNumber() == userId) {
                return account.getDeck();
            }
        }
        return std::vector<uint32_t>();
    }



private:
    void loadAccount(uint32_t userId);
    std::vector<Account> account_vector;
    Account* get_account(std::string id);
    Account* get_account(int u_num);
};



#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
