//
// Created by jacky on 2019/4/6.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H

#include <vector>
#include <string>
class Account{
public:
    Account(std::string &id, std::string &password);
    bool is_same(Account &another);
    bool is_same_id(std::string& other_id);
    bool login(std::string &password);
    void modify_password(std::string &password);
private:
    std::string id_;
    std::string password_;

};


class AccountSystem {

public:
    AccountSystem();
    bool create_account(std::string &id, std::string &password);
    bool exist(std::string &account_id);
    bool login(std::string &id, std::string &password);
    bool modify_password(std::string &id, std::string &ori_password, std::string &new_password);
private:
    std::vector<Account> account_vector;
    Account* get_account(std::string id);
};

#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
