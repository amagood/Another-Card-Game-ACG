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
#include "debug.h"
#include "roommode.h"


class AccountSystem {
public:
    AccountSystem();
    bool exist(std::string &account_name);
    bool exist(uint32_t userId);

    bool createAccount(std::string &id, std::string &password);
    bool login(std::string &account_name, std::string &password);
    bool logout(uint32_t userId);
    bool isOnline(uint32_t userId);

    bool modifyPassword(std::string &id, std::string &ori_password, std::string &new_password);
    bool modifyMoney(uint32_t userId, int money);
    bool modifyCards(uint32_t id, U32vec deck);
    bool update(uint32_t winner, uint32_t loser, RoomMode mode);
    bool addAllToDesk(uint32_t userId);
    uint32_t getUserId(std::string name);

    uint32_t getMoney(uint32_t userId);
    U32vec getCards(uint32_t userId);
    U32vec getDeck(uint32_t userId);
    std::string getAccountName(uint32_t userId);
    uint32_t getLadderPoint(uint32_t userId);
    std::string getLadderLevel(uint32_t userId);
    uint32_t getWin(uint32_t userId);
    uint32_t getLose(uint32_t userId);

    bool addCard(uint32_t userId, uint32_t cardId);

    void saveAccounts();


private:
    static void saveAccount(uint32_t userId, nlohmann::json &j);
    void loadAccounts();
    void loadAccount(uint32_t userId);
    std::vector<Account> account_vector;
    uint32_t lastId;
    Account* get_account(std::string id);
    Account* get_account(uint32_t u_num);
    bool deckIsLegal(U32vec deck, U32vec cards);
};



#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
