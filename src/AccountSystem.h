//
// Created by jacky on 2019/4/6.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H

#include <vector>
#include <string>
class Account{
public:
    Account(std::string &id, std::string &keyword_);
    bool is_same(Account &another);
    bool is_same_id(std::string& other_id);
    bool login(std::string &password);

private:
    std::string id_;
    std::string keyword_;

};


class AccountSystem {

public:
    AccountSystem();
    bool create_account(std::string id, std::string keyword);
    bool exist(std::string account_id);
    bool login(std::string id, std::string keyword);
private:
    std::vector<Account> account_vector;
    Account* get_account(std::string id);
};

#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
