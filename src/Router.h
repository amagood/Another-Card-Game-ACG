//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_ROUTER_H
#define ANOTHER_CARD_GAME_ACG_ROUTER_H

#include <nlohmann/json.hpp>

#include "Reader.h"
#include "Printer.h"
#include "AccountSystem.h"
#include "AccountSystemParser.h"


class Router {
public:
    Router();
    AccountSystemParser * accountSystemParser;
    void route();
    void run();
    void chooseDirection(nlohmann::json j);
    void setAccountSystems(AccountSystemController *);
    std::mutex routeMutex_;
    std::deque<nlohmann::json> routeDeque_;

private:

    std::mutex accountSystemMutex;
    std::deque<nlohmann::json> toAccountSystem;
};


#endif //ANOTHER_CARD_GAME_ACG_ROUTER_H
