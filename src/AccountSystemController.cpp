//
// Created by jacky on 2019-05-11.
//

#include "AccountSystemController.h"
#include "debug.h"
#include "DrawCardSystem.h"
#include "ACGType.h"

U32vec paramsToU32vec(nlohmann::json &data) {
    U32vec u32Vec;
    for (uint32_t i: data["params"]) {
        u32Vec.push_back(i);
    }
    return u32Vec;
}
StrVec paramsToStrVec(nlohmann::json &data) {
    StrVec strVec;
    for (std::string str: data["params"]) {
        strVec.push_back(str);
    }
    return strVec;
}
bool AccountSystemController::getAccountInfo(nlohmann::json &data, uint32_t userId) {
    error("AccountSystemController get info");
    U32vec params = paramsToU32vec(data);
    for (uint32_t userId: params) {
        if (!accountSystem->exist(userId)) {
            return false;
        }
        std::string stringId = std::to_string(userId);
        data["returnValue"][stringId]["accountName"] = accountSystem->getAccountName(userId);
        data["returnValue"][stringId]["money"] = accountSystem->getMoney(userId);
        data["returnValue"][stringId]["ladderPoint"] = accountSystem->getLadderPoint(userId);
        data["returnValue"][stringId]["ladderLevel"] = accountSystem->getLadderLevel(userId);
        data["returnValue"][stringId]["win"] = accountSystem->getWin(userId);
        data["returnValue"][stringId]["lose"] = accountSystem->getLose(userId);
    }
    return true;
}
bool AccountSystemController::getAccountName(nlohmann::json &data, uint32_t userID) {
    error("AccountSystemController getAccountName");
    U32vec params = paramsToU32vec(data);
    StrVec names;
    for (uint32_t i : params) {
        if (!accountSystem->exist(i)) {
            error("Account not exist");
            return false;
        }
        data["returnValue"][std::to_string(i)] = accountSystem->getAccountName(i);
    }
    return true;
}
bool AccountSystemController::createAccount(nlohmann::json &data, uint32_t userId) {
    error("AccountSystemController create account");
    StrVec params = paramsToStrVec(data);
    return accountSystem->createAccount(params[0], params[1]);
}

bool AccountSystemController::logout(nlohmann::json &data, uint32_t userId) {
    error("AccountSystemController log out");
    U32vec params = paramsToU32vec(data);
    return accountSystem->exist(params[0]) && accountSystem->logout(params[0]);
}
bool AccountSystemController::login(nlohmann::json &data, uint32_t userId) {
    error("AccountSystemController login");
    StrVec params = paramsToStrVec(data);
    if(accountSystem->exist(params[0]) && accountSystem->login(params[0], params[1])) {
        data["returnValue"]["connectionId"] = params[3];
        data["returnValue"]["userId"] = accountSystem->getUserId(params[0]);
        return true;
    } else {
        return false;
    }
}
bool AccountSystemController::payMoney(nlohmann::json &data, uint32_t userId) {
    error("AccountSystemController pay money");
    U32vec params = paramsToU32vec(data);
    bool success = accountSystem->exist(userId) && accountSystem->modifyMoney(userId, params[0]);
    if(success) {
        int money = accountSystem->getMoney(userId);
        data["returnValue"]["money"] = money;
    }
    return success;
}
bool AccountSystemController::drawCards(nlohmann::json &data, uint32_t userId) {
    error("AccountSystemController draw cards");
    U32vec params = paramsToU32vec(data);
    uint32_t times = params[0] / 100 + params[0] / 1000;

    if (accountSystem->exist(userId) && (accountSystem->getMoney(userId) >= params[0])) {
        accountSystem->modifyMoney(userId, -(int)params[0]);
        U32vec cardlist;
        while (times--) {
            uint32_t cardId = drawCardSystem->drawCard();
            cardlist.push_back(cardId);
            accountSystem->addCard(userId, cardId);
        }
        data["returnValue"]["money"] = accountSystem->getMoney(userId);
        data["returnValue"]["amount"] = times;
        data["returnValue"]["cards"] = cardlist;
        return true;
    }
    // money not enough
    return false;
}
bool AccountSystemController::getCards(nlohmann::json &data, uint32_t userId) {
    error("AccountSystemController getCards");
    U32vec params = paramsToU32vec(data);
    if (!accountSystem->exist(userId)) {
        return false;
    }
    data["returnValue"]["deck"] = accountSystem->getDeck(params[0]);
    data["returnValue"]["amounts"] = accountSystem->getCards(params[0]).size();
    data["returnValue"]["cards"] = accountSystem->getCards(params[0]);
    return true;
}
bool AccountSystemController::modifyCards(nlohmann::json &data, uint32_t userId) {
    error("AccountSystemController modify cards");
    U32vec params = paramsToU32vec(data);
    U32vec deck = data["deck"];
    if (accountSystem->exist(userId) && accountSystem->modifyCards(params[0], deck)) {
        data["returnValue"]["deck"] = accountSystem->getDeck(params[0]);
        data["returnValue"]["amounts"] = accountSystem->getCards(params[0]).size();
        data["returnValue"]["cards"] = accountSystem->getCards(params[0]);
    }
    return false;
}
bool AccountSystemController::getUserId(nlohmann::json &data, uint32_t userId) {
    error("Get UserId");
    StrVec params = paramsToStrVec(data);
    for (std::string name: params) {
        if(!accountSystem->exist(name)) {
            // account not exist
            return false;
        }
        data["returnVaule"][name] = accountSystem->getUserId(name);
    }
    return true;
}
bool AccountSystemController::addAllToDesk(nlohmann::json &data, uint32_t userId) {
    error("Add all to desk");
    U32vec params = paramsToU32vec(data);
    if(!accountSystem->exist(params[0])) {
        return false;
    }
    bool success = accountSystem->addAllToDesk(params[0]);
    data["returnValue"]["deck"] = accountSystem->getDeck(params[0]);
    data["returnValue"]["deckAmount"] = accountSystem->getDeck(params[0]).size();
    return success;
}

nlohmann::json AccountSystemController::run(nlohmann::json &j) {
    error("AccountSystemController Run");
    uint32_t userID = j["userId"];
    nlohmann::json data = j["data"];
    std::string func = data["function"];
    data["returnValue"] = nlohmann::json({});
    data["returnValue"]["success"] = (map_functions.count(func) > 0) && (map_functions.at(func)(*this, data, userID));
    j["data"] = data;
    return j;
}


AccountSystemController::AccountSystemController(AccountSystem * accountSystem1) {
    accountSystem = accountSystem1;
    drawCardSystem = new DrawCardSystem();
    map_functions = {
        {"getAccountName", &AccountSystemController::getAccountName},
        {"createAccount", &AccountSystemController::createAccount},
        {"login", &AccountSystemController::login},
        {"logout", &AccountSystemController::logout},
        {"getAccountInfo", &AccountSystemController::getAccountInfo},
        {"payMoney", &AccountSystemController::payMoney},
        {"drawCards", &AccountSystemController::drawCards},
        {"getCards", &AccountSystemController::getCards},
        {"getUserId", &AccountSystemController::getUserId},
        {"addAllToDesk", &AccountSystemController::addAllToDesk},
        {"modifyCards", &AccountSystemController::modifyCards}
    };
}



