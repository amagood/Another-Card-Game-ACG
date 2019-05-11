//
// Created by jacky on 2019-05-11.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMPARSER_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMPARSER_H

#include <queue>
#include <nlohmann/json.hpp>
#include "AccountSystem.h"

class AccountSystemParser {
public:
    void setIOQueue(std::queue<nlohmann::json> &in, std::mutex &in_mutex);
    void setAccountSystem(AccountSystem & accountSystem);
    void parse();
private:
    bool stop_parse = false;
    std::queue<nlohmann::json> * in_json_queue_;
    std::mutex * in_mutex_;
    AccountSystem * accountSystem_;

};


#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMPARSER_H
