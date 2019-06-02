//
// Created by jacky on 2019-05-11.
//

#include "AccountSystemController.h"
#include "debug.h"
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
    error("AccountSystemController Run");
    uint32_t userID = j["userId"];
    nlohmann::json data = j["data"];
    std::string func = data["function"];
    data["returnValue"] = nlohmann::json({});
    bool success = false;

    if(func == "getAccountName") {
        error("AccountSystemController getAccountName");
        U32vec params = paramsToU32vec(j);
        StrVec names;
        for (uint32_t i : params) {
            if (accountSystem->exist(i)) {
                data["returnValue"][std::to_string(i)] = accountSystem->getAccountName(i);
                success = true;
            }
        }

    } else if(func == "createAccount") {
        error("AccountSystemController create account");
        StrVec params = paramsToStrVec(j);
        success = accountSystem->createAccount(params[0], params[1]);
    } else if(func == "login") {
        error("AccountSystemController login");
        StrVec params = paramsToStrVec(j);
        success = accountSystem->login(params[0], params[1]);
    } else if (func == "logout") {
        error("AccountSystemController log out");
        U32vec params = paramsToU32vec(j);
        success = accountSystem->logout(params[0]);
    } else if (func == "getAccountInfo") {
        error("AccountSystemController get info");
        // TODO

        U32vec params = paramsToU32vec(j);
        bool flag = true;
        for (uint32_t userId: params) {
            if (!accountSystem->exist(userId)) {
                flag = false;
                break;
            }
            std::string stringId = std::to_string(userId);
            data["returnValue"][stringId]["accountName"] = accountSystem->getAccountName(userId);
            data["returnValue"][stringId]["money"] = accountSystem->getMoney(userId);
            data["returnValue"][stringId]["ladderPoint"] = accountSystem->getLadderPoint(userId);
            data["returnValue"][stringId]["ladderLevel"] = accountSystem->getLadderLevel(userId);
            data["returnValue"][stringId]["win"] = accountSystem->getWin(userId);
            data["returnValue"][stringId]["lose"] = accountSystem->getLose(userId);
        }
        if (flag) {
            success = true;
        } else {
            success = false;
        }

    } else if (func == "payMoney" && accountSystem->exist(userID)) {
        error("AccountSystemController pay money");
        U32vec params = paramsToU32vec(j);
        success = accountSystem->modifyMoney(userID, params[0]);
        if(success) {
            int money = accountSystem->getMoney(userID);
            data["returnValue"]["money"] = money;
        }
    } else if (func == "drawCards" && accountSystem->exist(userID)) {
        error("AccountSystemController draw cards");
        U32vec params = paramsToU32vec(j);

        uint32_t times = params[0] / 100;
        if (accountSystem->getMoney(userID) < params[0]) {
            // money isn't enough
            success = false;
        } else {
            accountSystem->modifyMoney(userID, -(int)params[0]);
            U32vec cardlist;
            if (times > 10) {
                cardlist.push_back(drawCardSystem->drawCard());
            }
            while (times--) {
                cardlist.push_back(drawCardSystem->drawCard());
            }
            for(uint32_t cardId: cardlist) {
                accountSystem->addCard(userID, cardId);
            }
            data["returnValue"]["money"] = accountSystem->getMoney(userID);
            if(params[0] == 100) {
                data["returnValue"]["amount"] = 1;
            } else {
                data["returnValue"]["amount"] = 11;
            }
            data["returnValue"]["cards"] = cardlist;
            success = true;
        }


    } else if (func == "getCards") {
        error("AccountSystemController getCards");
        U32vec params = paramsToU32vec(j);
        if (accountSystem->exist(params[0])){
            data["returnValue"]["deck"] = accountSystem->getDeck(params[0]);
            data["returnValue"]["amounts"] = accountSystem->getCards(params[0]).size();
            data["returnValue"]["cards"] = accountSystem->getCards(params[0]);
            success = true;
        } else {
            success = false;
        }

    } else if (func == "modifyCards") {
        error("AccountSystemController modify cards");
        U32vec params = paramsToU32vec(j);
        if (accountSystem->exist(params[0])) {
            U32vec deck = data["deck"];
            if (accountSystem->modifyCards(params[0], deck)) {
                data["returnValue"]["deck"] = accountSystem->getDeck(params[0]);
                data["returnValue"]["amounts"] = accountSystem->getCards(params[0]).size();
                data["returnValue"]["cards"] = accountSystem->getCards(params[0]);
                success = true;
            } else {
                success = false;
            }
        } else {
            success = false;
        }


    }
    if(success) {
        data["returnValue"]["0"] = "1";
    } else {
        data["returnValue"]["0"] = "0";
    }

    j["data"] = data;

    return j;
}


AccountSystemController::AccountSystemController(AccountSystem * accountSystem1) {
    accountSystem = accountSystem1;
    drawCardSystem = new DrawCardSystem();
}
