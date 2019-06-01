//
// Created by jacky on 2019/4/6.
//

#include "AccountSystem.h"

#include <stdexcept>
#include <chrono>
#include <thread>
#include <fstream>

#include <nlohmann/json.hpp>

#define SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))


AccountSystem::AccountSystem() {
    loadAccounts();
}
void AccountSystem::modifyCards(uint32_t id, U32vec cards, U32vec deck) {
    Account * acc = get_account(id);
    acc->setCards(cards);
    acc->setCards(deck);
}
void AccountSystem::loadAccounts() {
    std::ifstream file("data/accountlist.json");
    nlohmann::json json_;
    file >> json_;
    lastId = json_["accountIdLast"];
    std::vector<uint32_t> userIds = json_["accountlist"];

    for ( uint32_t userId :userIds ) {
        loadAccount(userId);
    }
}
void AccountSystem::loadAccount(uint32_t userId) {
    std::string dir = "data/account/";
    std::string filename = std::to_string(userId) + ".json";
    std::ifstream file(dir + filename);
    nlohmann::json json_;
    file >> json_;
    account_vector.push_back(Account(json_));
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
bool AccountSystem::modifyMoney(std::string &id, int money) {
    Account *account = get_account(id);
    if (account != nullptr) {
        return account->modifyMoney(money);
    } else {
        return false;
    }
}
bool AccountSystem::modifyMoney(uint32_t user_id_, int money) {
    Account *account = get_account(user_id_);
    if (account != nullptr) {
        return account->modifyMoney(money);
    } else {
        return false;
    }
}
void AccountSystem::saveAccount(int userId, nlohmann::json j) {
    std::string dir = "data/account/";
    std::string filename = std::to_string(userId) + ".json";
    error(j);
    std::ofstream file(dir + filename);
    file << j;
}
int AccountSystem::getMoney(std::string &id) {
    Account *account = get_account(id);
    if (account != nullptr) {
        return account->getMoney();
    } else {
        return -1;
    }
}

bool AccountSystem::logout(uint32_t user_id_) {
    Account *account = get_account(user_id_);
    if(account->isOnline()) {
        account->left();
        return true;
    }
    return false;
}
bool AccountSystem::logout(std::string &account_name) {
    Account *account = get_account(account_name);
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
void AccountSystem::load() {
    // load cardlist
}

uint32_t AccountSystem::getUUId(std::string &account_name) {
    Account * a = get_account(account_name);

    return a->getUUID();
}

bool AccountSystem::uuidExist(uint32_t i) {
    Account * a = get_account(i);
    return a != nullptr;
}

#undef SLEEP
