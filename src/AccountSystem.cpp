//
// Created by jacky on 2019/4/6.
//

#include "AccountSystem.h"

#include <nlohmann/json.hpp>

#include <stdexcept>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <fstream>

#define SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))

Account::Account(std::string &id, std::string &password) {
    id_ = id;
    password_ = password;
}
Account::Account(nlohmann::json j) {
    user_id_ = j["userId"];
    name_ = j["name"];
    password_ = j["password"];
    win_ = j["win"];
    lose_ = j["lose"];
    ladderPoint_ = j["ladderPoint"];
    std::vector<uint32_t > d = j["deck"];
    std::vector<uint32_t > c = j["cards"];
    ladderLevel = j["ladderLevel"];
    deck_card_list = d;
    card_list = c;
}
nlohmann::json Account::toJson() {
    nlohmann::json j;
    j["userId"] = user_id_;
    j["name"] = name_;
    j["password"] = password_;
    j["win"] = win_ ;
    j["lose"] = lose_;
    j["ladderPoint"] = ladderPoint_;
    j["deck"] = deck_card_list;
    j["cards"] = card_list;
    j["ladderLevel"] = ladderLevel;
    return j;
}
void Account::modifyPassword(std::string &password){
    password_ = password;
}

bool Account::isIDSame(std::string &other_id) {
    return this->id_ == other_id;
}
bool Account::isSame(Account &another) {
    return this->isIDSame(another.id_);
}
int Account::getMoney() {
    return money_;
}
void Account::modifyMoney(int money) {
    money_ += money;
}


AccountSystem::AccountSystem() {
    loadAccounts();
}

void AccountSystem::loadAccounts() {
    nlohmann::json jsonfile;
    std::ifstream file("data/accountlist.json");
    jsonfile << file;
    std::vector<uint32_t> userIds = jsonfile["accountlist"];
    for ( uint32_t userId :userIds ) {
        loadAccount(userId);
    }
}
void AccountSystem::loadAccount(uint32_t userId) {
    std::string dir = "data/account/";
    std::string filename = std::to_string(userId) + ".json";
    std::ifstream file(dir + filename);
    nlohmann::json jsonfile;
    jsonfile << file;
    account_vector.push_back(Account(jsonfile));
}
void AccountSystem::saveAccounts() {
    for (Account &account : account_vector) {
        nlohmann::json j = account.toJson();
        saveAccount(account.getUniqueNumber(), j);
    }
}

bool Account::verify(std::string &password) {
    // TODO revise with encryption
    return password_ == password;
}

bool AccountSystem::login(std::string &account_name, std::string &password) {
    if (!this->exist(account_name)) {
        return false;
    } else {
        Account *account = this->get_account(account_name);
        return account->verify(password);
    }
}
bool AccountSystem::createAccount(std::string &id, std::string &password) {
    // test is exist
    if (this->exist(id)) {
        return false;
    }
    this->account_vector.emplace_back(Account(id, password));
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
Account* AccountSystem::get_account(int u_num) {
    for (Account &a: account_vector) {
        if(a.getUniqueNumber() == u_num) {
            return &a;
        }
    }
    return nullptr;
}
void AccountSystem::modifyMoney(std::string &id, int money) {
    Account *account = get_account(id);
    if (account != nullptr) {
        account->modifyMoney(money);
    }
}
void AccountSystem::modifyMoney(uint32_t user_id_, int money) {
    Account *account = get_account(user_id_);
    if (account != nullptr) {
        account->modifyMoney(money);
    }
}
void AccountSystem::saveAccount(int userId, nlohmann::json j) {
    std::string dir = "data/account/";
    std::string filename = std::to_string(userId) + ".json";
    std::ofstream file(dir + filename);
    nlohmann::json jsonfile;
    file << jsonfile;
}
int AccountSystem::getMoney(std::string &id) {
    Account *account = get_account(id);
    if (account != nullptr) {
        return account->getMoney();
    } else {
        return -1;
    }
}



#undef SLEEP
