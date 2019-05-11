//
// Created by jacky on 2019/4/6.
//

#include "AccountSystem.h"

#include <stdexcept>
#include <chrono>
#include <thread>
#include <string>
#include <vector>

#define SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))

Account::Account(std::string &id, std::string &password) {
    id_ = id;
    password_ = password;
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


AccountSystem::AccountSystem() = default;

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
void AccountSystem::saveAccount(int u_num) {
    Account * account = get_account(u_num);
    // save info
    // user_id_.txt is file name
    //
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
