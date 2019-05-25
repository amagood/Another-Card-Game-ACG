//
// Created by jacky on 2019-05-11.
//

#include "AccountSystemController.h"

#include "DrawCardSystem.h"
#include "ACGType.h"
U32vec paramsToU32vec(nlohmann::json &j) {
    U32vec u32Vec;
    for (uint32_t i: j["data"]["params"]) {
        u32Vec.push_back(i);
    }
    return u32Vec;
}
StrVec paramsToStrVec(nlohmann::json &j) {
    StrVec strVec;
    for (std::string str: j["data"]["params"]) {
        strVec.push_back(str);
    }
    return strVec;
}

nlohmann::json AccountSystemController::run(nlohmann::json &j) {

    uint32_t userID = j["userId"];
    nlohmann::json data = j["data"];
    std::string func = data["function"];
    data["returnValue"] = nlohmann::json();
    bool success = false;

    if(func == "getAccountName") {
        U32vec params = paramsToU32vec(j);
        StrVec names;
        for (uint32_t i : params) {
            data["returnValue"][std::to_string(i)] = accountSystem->getAccountName(i);
        }
        success = true;
    } else if(func == "createAccount") {
        StrVec params = paramsToStrVec(j);
        success = accountSystem->createAccount(params[0], params[1]);
    } else if(func == "login") {
        StrVec params = paramsToStrVec(j);
        success = accountSystem->login(params[0], params[1]);
    } else if (func == "getAccountInfo") {
        // TODO
        U32vec params = paramsToU32vec(j);
        accountSystem->getAccountInfo(params[0]);
        success = true;
    } else if (func == "logout") {
        U32vec params = paramsToU32vec(j);
        success = accountSystem->logout(params[0]);
    } else if (func == "payMoney") {
        U32vec params = paramsToU32vec(j);
        success = accountSystem->modifyMoney(userID, params[0]);
    } else if (func == "drawCards") {
        U32vec params = paramsToU32vec(j);
        uint32_t times = params[0] / 100;
        U32vec cardlist;
        if(times > 100) {
            success = false;
        } else {
            if (times > 10) {
                cardlist.push_back(drawCardSystem->drawCard());
            }
            while (times--) {
                cardlist.push_back(drawCardSystem->drawCard());
            }
        }
        for(uint32_t cardId: cardlist) {
            accountSystem->addCard(userID, cardId);
        }

        data["returnValue"]["money"] = params[0];
        if(params[0] == 100) {
            data["returnValue"]["amount"] = 1;
        } else {
            data["returnValue"]["amount"] = 11;
        }
        success = true;

    } else if (func == "getCards") {
        U32vec params = paramsToU32vec(j);
        U32vec cards = accountSystem->getCards(params[0]);
        U32vec deck = accountSystem->getDeck(params[0]);
        uint32_t amount = accountSystem->getCards(params[0]).size();
        data["returnValue"]["deck"] = amount;
        data["returnValue"]["amounts"] = amount;
        data["returnValue"]["cards"] = cards;
        success = true;
    } else if (func == "modifyCards") {
        U32vec params = paramsToU32vec(j);
        U32vec cards = data["paramsMap"]["cards"];
        U32vec deck = data["paramsMap"]["deck"];
        accountSystem->modifyCards(params[0], cards, deck);
    }
    j["data"] = data;
    if(success) {
        data["returnValue"]["0"] = "1";
    } else {
        data["returnValue"]["0"] = "0";
    }
    return j;
}


AccountSystemController::AccountSystemController(AccountSystem * accountSystem1) {
    accountSystem = accountSystem1;
    drawCardSystem = new DrawCardSystem();
}
//
//void AccountSystemController::createAccount(std::string id, std::string password) {
//    bool success = accountSystem->createAccount(id, password);
//    // TODO
//}
//void AccountSystemController::getAccountsName(std::vector<uint32_t> userIds) {
//    nlohmann::json ans;
//    for (uint32_t& id : userIds) {
//        std::string name = accountSystem->getAccountName(id);
//        ans[id] = name;
//    }
//}
//void AccountSystemController::login(std::string name, std::string password) {
//    accountSystem->login(name, password);
//}
//void AccountSystemController::logout(uint32_t userId) {
//    accountSystem->logout(userId);
//}
//void AccountSystemController::payMoney(uint32_t userId, int number) {
//    accountSystem->modifyMoney(userId, number);
//}
//
//void AccountSystemController::drawCards(uint32_t userId, int card_amount) {
//    for (int i = 0; i < card_amount; i++) {
//        uint32_t cardId = drawCardSystem->drawCard();
//        if (!accountSystem->addCard(userId, cardId)) {
//            //Todo raise error
//            return;
//        }
//    }
//}
//void AccountSystemController::getCards(uint32_t userId) {
//    std::vector<uint32_t> cards = accountSystem->getCards(userId);
//    accountSystem->getDeck(userId);
//}
//void AccountSystemController::modifyCards(uint32_t userId, std::vector<uint32_t> cards, std::vector<uint32_t> decks)
//{
//    accountSystem->updateCards(userId, cards, decks);
//    accountSystem->getDeck(userId);
//    accountSystem->getCards(userId);
//}
//void AccountSystemController::getAccountInfo(uint32_t userId) {
//
//
//}