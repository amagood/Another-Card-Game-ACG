//
// Created by jacky on 2019/4/6.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H

#include "Account.h"

#include <string>
#include <queue>
#include <mutex>

#include <nlohmann/json.hpp>

#include "ACGType.h"

class AccountSystem {
public:

    AccountSystem();
    bool createAccount(std::string &id, std::string &password);
    bool exist(std::string &account_name);
    bool login(std::string &account_name, std::string &password);
    bool logout(uint32_t user_id_);
    bool logout(std::string &account_name);
    bool isOnline(uint32_t user_id_) {
        return get_account(user_id_)->isOnline();
    }
    bool modifyPassword(std::string &id, std::string &ori_password, std::string &new_password);
    bool modifyMoney(std::string &id, int money);
    bool modifyMoney(uint32_t user_id_, int money);
    int getMoney(std::string &id);
    void loadAccounts();

    void saveAccount(int u_num, nlohmann::json j);
    void updateCards(uint32_t userId, U32vec cards, U32vec deck) {
        get_account(userId)->setDeck(deck);
        get_account(userId)->setCards(cards);
    }
    void saveAccounts();
    void modifyCards(uint32_t id, U32vec, U32vec);
    void getAccountInfo(uint32_t u_num){};
    U32vec getCards(uint32_t userId) {
        return get_account(userId)->getCards();
    }
    bool addCard(uint32_t userId, uint32_t cardId);
    std::string getAccountName(uint32_t user_id_){
        return get_account(user_id_)->getName();
    };

    U32vec getDeck(uint32_t userId) {

        return get_account(userId)->getDeck();
    }

    std::string getAccountDeviceId(uint32_t uint32);

private:
    void load();
    void loadAccount(uint32_t userId);
    std::vector<Account> account_vector;
    Account* get_account(std::string id);
    Account* get_account(uint32_t u_num);

};



#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
