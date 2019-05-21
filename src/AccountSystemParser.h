//
// Created by jacky on 2019-05-11.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMPARSER_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMPARSER_H

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "AccountSystemController.h"

class AccountSystemParser {
public:
    AccountSystemParser(std::deque<nlohmann::json> &in, std::mutex &in_mutex);
    void setAccountSystemController(AccountSystemController * accountSystemController);
    void parse();
private:
    bool stop_parse = false;
    std::deque<nlohmann::json> * in_json_deque_;
    std::mutex * in_mutex_;
    AccountSystemController * accountSystemController_;
};


#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMPARSER_H
