//
// Created by jacky on 2019/4/6.
//

#include "AccountSystem.h"

#include <stdexcept>
#include <chrono>
#include <thread>
#include <fstream>
#include <algorithm>
#include <nlohmann/json.hpp>
#include "roommode.h"
#define SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))


AccountSystem::AccountSystem() {
    loadAccounts();
}
bool AccountSystem::modifyCards(uint32_t id, U32vec deck) {
    Account *acc = get_account(id);
    U32vec cards = acc->getCards();
    if (deckIsLegal(deck, cards)) {
        acc->setDeck(deck);
        return true;
    } else {
        return false;
    }
}
bool AccountSystem::deckIsLegal(U32vec deck, U32vec cards) {
    for(uint32_t card : deck) {
        auto u32vecIter = std::find(cards.begin(), cards.end(), card);
        if(u32vecIter == cards.end()) {
            return false;
        } else {
            *u32vecIter = -1;
        }
    }
    return true;
}
void AccountSystem::loadAccounts() {
    nlohmann::json json_;
    try {
        std::ifstream file("data/accountlist.json");
        file >> json_;
        lastId = json_["accountIdLast"];
    } catch (nlohmann::json::parse_error &){
        error("file data/accountlist.json error");
        error("Can't not read data/accountlist.json atribuite which is \"accountIdLast\": u32int_t");
        lastId = 1;
        return;
    }

    try {
        std::vector<uint32_t> userIds = json_["accountlist"];
        for ( uint32_t userId :userIds ) {
            loadAccount(userId);
        }
    } catch (nlohmann::json::parse_error &) {
        error("file data/accountlist.json error");
        error("Can't not read data/accountlist.json atribuite which is \"accountlist\": U32vec");
        lastId = 1;
        return;
    }


}
void AccountSystem::loadAccount(uint32_t userId) {
    try {
        std::string dir = "data/account/";
        std::string filename = std::to_string(userId) + ".json";
        std::ifstream file(dir + filename);
        nlohmann::json json_;
        file >> json_;
        account_vector.push_back(Account(json_));
    } catch (nlohmann::json::parse_error &){
        error("file data/account/" << userId << ".json error");
    }

}
void AccountSystem::saveAccounts() {
    std::ofstream file("data/accountlist.json");
    nlohmann::json json_({});


    json_["accountIdLast"] = lastId;
    std::vector<uint32_t> uids;
    for (Account &account : account_vector) {
        uids.push_back(account.getUniqueNumber());
        nlohmann::json j = account.toJson();
        saveAccount(account.getUniqueNumber(), j);
    }
    json_["accountlist"] = uids;
    file << json_;

}

bool Account::verify(std::string password) {
    // TODO revise with encryption
    return password_ == password;
}

bool AccountSystem::login(std::string &account_name, std::string &password) {
    if (!this->exist(account_name)) {
        return false; // error account
    } else {
        Account *account = this->get_account(account_name);
        if (!account->verify(password)) {
            return false;
        }
        if (!account->isOnline()) {
            account->login();
            return true;
        }

    }
    return false;
}
bool AccountSystem::createAccount(std::string &id, std::string &password) {
    // test is exist
    if (this->exist(id)) {
        return false;
    }
    this->account_vector.emplace_back(Account(id, password, lastId));
    lastId ++;
    return true;
}

bool AccountSystem::exist(std::string &account_name) {

    for (Account &a : account_vector) {
        if(a.isIDSame(account_name))
            return true;
    }
    return false;
}
bool AccountSystem::modifyPassword(std::string &id, std::string &ori_password, std::string &new_password) {
    if (login(id, ori_password)) {
        Account *account = get_account(id);
        account->modifyPassword(new_password);
        return true;
    } else {
        return false;
    }

}
Account* AccountSystem::get_account(std::string id) {
    for (Account &a: account_vector) {
        if(a.isIDSame(id)) {
            return &a;
        }
    }
    return nullptr;
}
Account* AccountSystem::get_account(uint32_t u_num) {
    for (Account &a: account_vector) {
        if(a.getUniqueNumber() == u_num) {
            return &a;
        }
    }
    return nullptr;
}
bool AccountSystem::modifyMoney(uint32_t user_id_, int money) {
    Account *account = get_account(user_id_);
    if (account != nullptr) {
        return account->modifyMoney(money);
    } else {
        return false;
    }
}
void AccountSystem::saveAccount(uint32_t userId, nlohmann::json &j) {
    std::string dir = "data/account/";
    std::string filename = std::to_string(userId) + ".json";
    error(j);
    std::ofstream file(dir + filename);
    file << j;
}
uint32_t AccountSystem::getMoney(uint32_t userId) {
    Account *account = get_account(userId);
    if (account != nullptr) {
        return account->getMoney();
    } else {
        return -1;
    }
}

bool AccountSystem::logout(uint32_t userId) {
    Account *account = get_account(userId);
    if(account->isOnline()) {
        account->left();
        return true;
    }
    return false;
}
bool AccountSystem::addCard(uint32_t userId, uint32_t cardId) {
    Account *account = get_account(userId);
    return account->addCard(cardId);
}

bool AccountSystem::exist(uint32_t userId) {
    Account * a = get_account(userId);
    return a != nullptr;
}
std::string AccountSystem::getAccountName(uint32_t userId) {
    error("get Account Name");
    return get_account(userId)->getName();
}


U32vec AccountSystem::getDeck(uint32_t userId) {
    return get_account(userId)->getDeck();
}

U32vec AccountSystem::getCards(uint32_t userId) {
    return get_account(userId)->getCards();
}

bool AccountSystem::isOnline(uint32_t userId)  {
    return get_account(userId)->isOnline();
}

uint32_t AccountSystem::getLadderPoint(uint32_t userId){
    return get_account(userId)->getLadderPoint();
}
std::string AccountSystem::AccountSystem::getLadderLevel(uint32_t userId) {
    return get_account(userId)->getLadderLevel();
}
uint32_t AccountSystem::getWin(uint32_t userId) {
    return get_account(userId)->getWin();
}
uint32_t AccountSystem::getLose(uint32_t userId) {
    return get_account(userId)->getLose();
}

bool AccountSystem::update(uint32_t winner, uint32_t loser, RoomMode mode) {
    Account *winnerA = get_account(winner);
    Account *loserA = get_account(loser);

    if (mode == SINGLE_ROOM) {
        winnerA->win();
        loserA->lose();
        winnerA->recordHistory(loser, true, SINGLE_ROOM);
        loserA->recordHistory(winner, false, SINGLE_ROOM);
    } else if (mode == LADDER_ROOM) {
        winnerA->ladderWin();
        loserA->ladderLose();
        winnerA->recordHistory(loser, true, LADDER_ROOM);
        loserA->recordHistory(winner, false, LADDER_ROOM);
    } else if (mode == ONEONONE_ROOM) {
        winnerA->win();
        loserA->lose();
        winnerA->recordHistory(loser, true, ONEONONE_ROOM);
        loserA->recordHistory(winner, false, ONEONONE_ROOM);
    }

    return false;
}

uint32_t AccountSystem::getUserId(std::string name) {
    return get_account(name)->getUniqueNumber();
}

bool AccountSystem::addAllToDesk(uint32_t userId) {
    Account * account = get_account(userId);
    account->setDeck(account->getCards(30));
    return true;
}

bool AccountSystem::addCards(uint32_t userId, U32vec cardIds) {
    for (uint32_t cardId: cardIds) {
        if (!addCard(userId, cardId)) {
            return false;
        }
    }
    return true;
}

uint32_t AccountSystem::getLevel(uint32_t userId) {
    return get_account(userId)->getLevel();
}

uint32_t AccountSystem::getExp(uint32_t userId) {
    return get_account(userId)->getExp();
}


#undef SLEEP
