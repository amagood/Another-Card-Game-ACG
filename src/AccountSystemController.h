//
// Created by jacky on 2019-05-11.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H

#include <mutex>

#include "AccountSystem.h"
#include "DrawCardSystem.h"
#include <unordered_map>
class AccountSystemController {
    AccountSystem * accountSystem;
    DrawCardSystem * drawCardSystem;
    std::unordered_map<std::string,
      std::function<bool(AccountSystemController&, nlohmann::json &, uint32_t)>> map_functions;
//    std::unordered_map<std::string,
//            bool(AccountSystemController&)(nlohmann::json &, uint32_t)> map_functions;

    bool getAccountName(nlohmann::json &data, uint32_t userId);
    bool createAccount(nlohmann::json &data, uint32_t userId);
    bool login(nlohmann::json &data, uint32_t userId);
    bool logout(nlohmann::json &data, uint32_t userId);
    bool getAccountInfo(nlohmann::json &data, uint32_t userId);
    bool payMoney(nlohmann::json &data, uint32_t userId);
    bool drawCards(nlohmann::json &data, uint32_t userId);
    bool getCards(nlohmann::json &data, uint32_t userId);
    bool modifyCards(nlohmann::json &data, uint32_t userId);
    bool getUserId(nlohmann::json &data, uint32_t userId);
    bool addAllToDesk(nlohmann::json &data, uint32_t userId);
public:
    AccountSystemController(AccountSystem *);
    nlohmann::json run(nlohmann::json &);
};

#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H
