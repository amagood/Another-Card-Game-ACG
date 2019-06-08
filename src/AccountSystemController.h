//
// Created by jacky on 2019-05-11.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H

#include "nlohmann/json.hpp"
#include <unordered_map>

class AccountSystem;
class AccountSystemCommand;
class AccountSystemController {
    std::unordered_map<std::string, AccountSystemCommand *> map_functions;
public:
    explicit AccountSystemController(AccountSystem *);
    nlohmann::json run(nlohmann::json &);
};

#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H
