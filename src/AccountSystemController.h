//
// Created by jacky on 2019-05-11.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H

#include <mutex>

#include "AccountSystem.h"
#include "DrawCardSystem.h"

class AccountSystemController {
    AccountSystem * accountSystem;
    DrawCardSystem * drawCardSystem;
    std::mutex accountSystemMutex;
public:
    AccountSystemController();
    void getAccountsName(std::vector<uint32_t> userIds);
    void createAccount(std::string id, std::string password);
    void login(std::string id, std::string password);
    void logout(uint32_t userId);
    void payMoney(uint32_t userId, int number);
    void drawCards(uint32_t userId, int number);
    void getCards(uint32_t userId);
    void modifyCards(uint32_t userId, std::vector<uint32_t> cards, std::vector<uint32_t> decks);
    void getAccountInfo(uint32_t userId);
    std::mutex * getAccountSystemMutex();
    AccountSystem * getAccountSystem();
};


#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H
