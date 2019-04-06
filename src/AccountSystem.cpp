//
// Created by jacky on 2019/4/6.
//

#include "AccountSystem.h"
Account::Account(std::string &id, std::string &password) {
    id_ = id;
    password_ = password;
}
bool Account::is_same_id(std::string &other_id) {
    return this->id_ == other_id;
}
bool Account::is_same(Account &other) {
    return this->is_same_id(other.id_);
}

AccountSystem::AccountSystem() = default;

bool Account::login(std::string &password) {
    // TODO revise with encryption
    return password_ == password;
}

bool AccountSystem::login(std::string &id, std::string &password) {
    if (!this->exist(id)) {
        return false;
    } else {
        Account *account = this->get_account(id);
        return account->login(password);
    }
}
bool AccountSystem::create_account(std::string &id, std::string &password) {
    // test is exist
    if (this->exist(id)) {
        return false;
    }
    this->account_vector.emplace_back(Account(id, password));
    return true;
}

bool AccountSystem::exist(std::string &account_id) {
    for (Account &a : account_vector) {
        if(a.is_same_id(account_id))
            return true;
    }
    return false;
}

Account* AccountSystem::get_account(std::string id) {
    for (Account &a: account_vector) {
        if(a.is_same_id(id)) {
            return &a;
        }
    }
    return nullptr;
}
