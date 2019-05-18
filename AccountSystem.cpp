//
// Created by jacky on 2019/4/6.
//

#include "AccountSystem.h"
Account::Account(std::string &id, std::string &password) {
    id_ = id;
    password_ = password;
}
void Account::modify_password(std::string &new_password){
    password_ = new_password;
}

bool Account::is_same_id(std::string &other_id) {
    return this->id_ == other_id;
}
bool Account::is_same(Account &other) {
    return this->is_same_id(other.id_);
}
int Account::get_money() {
    return money_;
}
void Account::modify_money(int money) {
    money_ += money;
}


AccountSystem::AccountSystem() = default;

bool Account::verify(std::string &password) {
    // TODO revise with encryption
    return password_ == password;
}

bool AccountSystem::login(std::string &id, std::string &password) {
    if (!this->exist(id)) {
        return false;
    } else {
        Account *account = this->get_account(id);
        return account->verify(password);
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
bool AccountSystem::modify_password(std::string &id, std::string &ori_password, std::string &new_password) {
    if (login(id, ori_password)) {
        Account *account = get_account(id);
        account->modify_password(new_password);
        return true;
    } else {
        return false;
    }

}
Account* AccountSystem::get_account(std::string id) {
    for (Account &a: account_vector) {
        if(a.is_same_id(id)) {
            return &a;
        }
    }
    return nullptr;
}
Account* AccountSystem::get_account(int u_num) {
    for (Account &a: account_vector) {
        if(a.get_unique_num() == u_num) {
            return &a;
        }
    }
    return nullptr;
}
void AccountSystem::modify_money(std::string &id, int money) {
    Account *account = get_account(id);
    if (account != nullptr) {
        account->modify_money(money);
    }
}
void AccountSystem::save_account(int u_num) {
    Account * account = get_account(u_num);
    // save info
    // u_num.txt is file name
    //
}
int AccountSystem::get_money(std::string &id) {
    Account *account = get_account(id);
    if (account != nullptr) {
        return account->get_money();
    } else {
        return -1;
    }
}
