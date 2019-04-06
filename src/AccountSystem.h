//
// Created by jacky on 2019/4/6.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H

#include <vector>
#include <string>
class Account{

};
class AccountSystem {

public:
    AccountSystem();
    bool createAccount(const std::string account, const std::string keyword);
    bool isAccountExist(const std::string account);

private:
    std::vector<Account> accountVector;

};

#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
