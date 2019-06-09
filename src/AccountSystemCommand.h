//
// Created by jacky on 2019/6/9.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCOMMAND_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCOMMAND_H

#include "nlohmann/json.hpp"
#include "AccountSystem.h"
#include "DrawCardSystem.h"
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
class AccountSystemCommand {
protected:
    AccountSystem * accountSystem;
public:
    explicit AccountSystemCommand(AccountSystem * accountSystem_) {
        accountSystem = accountSystem_;
    }
    virtual bool execute(nlohmann::json &json, uint32_t userId) = 0;
};

class LoginCommand : public AccountSystemCommand {
public:
    explicit LoginCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("AccountSystemController login");
        StrVec params = paramsToStrVec(data);
        if(params.size() != 3) {
            error("ERROR: login error, your params amount should be 3!!!");
            error("ERROR: name, passwd, connectionId !!!");
            return false;
        }
        if(accountSystem->exist(params[0]) && accountSystem->login(params[0], params[1])) {
            data["returnValue"]["connectionId"] = params[2];
            data["returnValue"]["userId"] = accountSystem->getUserId(params[0]);
            return true;
        } else {
            return false;
        }
    }
};
class LogoutCommand : public AccountSystemCommand {
public:
    explicit LogoutCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("AccountSystemController log out");
        U32vec params = paramsToU32vec(data);
        if(params.size() != 1) {
            error("ERROR: logout error, your params amount should be 1!!!");
            error("ERROR: userId !!!");
            return false;
        }
        return accountSystem->exist(params[0]) && accountSystem->logout(params[0]);
    }
};

class GetCardsCommand : public AccountSystemCommand {
public:
    explicit GetCardsCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
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
};

class GetAccountInfoCommand : public AccountSystemCommand {
public:
    explicit GetAccountInfoCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("AccountSystemController get info");
        U32vec params = paramsToU32vec(data);
        for (uint32_t userId: params) {
            if (!accountSystem->exist(userId)) {
                error("ERROR: Account not exist");
                return false;
            }
            std::string stringId = std::to_string(userId);
            data["returnValue"][stringId]["accountName"] = accountSystem->getAccountName(userId);
            data["returnValue"][stringId]["money"] = accountSystem->getMoney(userId);
            data["returnValue"][stringId]["ladderPoint"] = accountSystem->getLadderPoint(userId);
            data["returnValue"][stringId]["ladderLevel"] = accountSystem->getLadderLevel(userId);
            data["returnValue"][stringId]["win"] = accountSystem->getWin(userId);
            data["returnValue"][stringId]["lose"] = accountSystem->getLose(userId);
            data["returnValue"][stringId]["level"] = accountSystem->getLevel(userId);
            data["returnValue"][stringId]["exp"] = accountSystem->getExp(userId);

        }
        return true;
    }
};

class GetAccountNameCommand : public AccountSystemCommand {
public:
    explicit GetAccountNameCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("AccountSystemController getAccountName");
        U32vec params = paramsToU32vec(data);
        StrVec names;
        for (uint32_t i : params) {
            if (!accountSystem->exist(i)) {
                error("ERROR: Account not exist");
                return false;
            }
            data["returnValue"][std::to_string(i)] = accountSystem->getAccountName(i);
        }
        return true;
    }
};

class CreateAccountCommand : public AccountSystemCommand {
private:
    DrawCardSystem drawCardSystem;
public:
    explicit CreateAccountCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("AccountSystemController create account");
        StrVec params = paramsToStrVec(data);
        if(params.size() != 3) {
            error("ERROR: Create account error, your params amount should be 3!!!");
            error("ERROR: name, passwd, connectionId !!!");
            return false;
        }
        if (accountSystem->createAccount(params.at(0), params.at(1))) {
            // initial account setting
            data["returnValue"]["connectionId"] = params.at(2);
            data["returnValue"]["userId"] = accountSystem->getUserId(params.at(0));
            U32vec cardIds = drawCardSystem.drawCards(30);
            uint32_t userId = accountSystem->getUserId(params.at(0));
            accountSystem->addCards(userId, cardIds);
            accountSystem->addAllToDesk(userId);
            return true;
        } else {
            return false;
        }
    }
};

class PayMoneyCommand : public AccountSystemCommand {
public:
    explicit PayMoneyCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("AccountSystemController pay money");
        U32vec params = paramsToU32vec(data);
        if(params.size() != 1) {
            error("ERROR: PayMoney error, your params amount should be 1!!!");
            error("ERROR: money !!!");
            return false;
        }
        int money_ = params.at(0);
        bool success = accountSystem->exist(userId) && accountSystem->modifyMoney(userId, money_);
        if(success) {
            int money = accountSystem->getMoney(userId);
            data["returnValue"]["money"] = money;
        }
        return success;
    }
};

class DrawCardCommand : public AccountSystemCommand {
    DrawCardSystem drawCardSystem;
public:
    explicit DrawCardCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("AccountSystemController draw cards");
        U32vec params = paramsToU32vec(data);
        if(params.size() != 1) {
            error("ERROR: DrawCards error, your params amount should be 1!!!");
            error("ERROR: money !!!");
            return false;
        }
        int money = (int)params.at(0);
        uint32_t times = money / 100 + money / 1000;

        if (accountSystem->exist(userId) && (accountSystem->getMoney(userId) >= money)) {
            accountSystem->modifyMoney(userId, -money);
            U32vec cardlist = drawCardSystem.drawCards(times);
            accountSystem->addCards(userId, cardlist);
            data["returnValue"]["money"] = accountSystem->getMoney(userId);
            data["returnValue"]["amount"] = times;
            data["returnValue"]["cards"] = cardlist;
            return true;
        }
        // money not enough
        return false;
    }
};
class ModifyCards : public AccountSystemCommand {
public:
    explicit ModifyCards(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("AccountSystemController modify cards");
        U32vec params = paramsToU32vec(data);
        if(params.size() == 0 || data.count("deck") == 0) {
            error("ERROR: modifyCards error!");
            error("ERROR: your params amount should be 1 and \"deck\" should exist!");
            return false;
        }
        U32vec deck = data["deck"];
        if (accountSystem->exist(userId) && accountSystem->modifyCards(params[0], deck)) {
            data["returnValue"]["deck"] = accountSystem->getDeck(params[0]);
            data["returnValue"]["amounts"] = accountSystem->getCards(params[0]).size();
            data["returnValue"]["cards"] = accountSystem->getCards(params[0]);
            return true;
        }
        return false;
    }
};
class GetUserIdCommand : public AccountSystemCommand {
public:
    explicit GetUserIdCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("Get UserId");
        StrVec params = paramsToStrVec(data);
        for (std::string name: params) {
            if(!accountSystem->exist(name)) {
                error("account not exist");
                return false;
            }
            data["returnVaule"][name] = accountSystem->getUserId(name);
        }
        return true;
    }
};
class AddAllToDeckCommand : public AccountSystemCommand {
public:
    explicit AddAllToDeckCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("Add all to desk");
        U32vec params = paramsToU32vec(data);
        if(params.size() != 1) {
            error("ERROR: AddAllToDesk error, your params amount should be 1!!!");
            error("ERROR: userId!!!");
            return false;
        }
        uint32_t userId_p = params.at(0);
        if(!accountSystem->exist(userId_p)) {
            error("account not exist");
            return false;
        }
        bool success = accountSystem->addAllToDesk(userId_p);
        data["returnValue"]["deck"] = accountSystem->getDeck(userId_p);
        data["returnValue"]["deckAmount"] = accountSystem->getDeck(userId_p).size();
        return success;
    }
};

class GetDeckCommand : public AccountSystemCommand {
public:
    explicit GetDeckCommand(AccountSystem * accountSystem_) : AccountSystemCommand(accountSystem_){};
    bool execute(nlohmann::json &data, uint32_t userId) override {
        error("Get desk");
        U32vec params = paramsToU32vec(data);
        uint32_t userId_p = params.at(0);
        if (accountSystem->exist(userId_p)) {
            data["returnValue"]["deck"] = accountSystem->getDeck(userId_p);
            data["returnValue"]["amounts"] = accountSystem->getDeck(userId_p).size();
            return true;
        }
        return false;
    }
};
#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCOMMAND_H
