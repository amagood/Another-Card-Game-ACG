//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_ROUTER_H
#define ANOTHER_CARD_GAME_ACG_ROUTER_H

#include <string>
#include <queue>

#include "nlohmann/json.hpp"

#include "Reader.h"
#include "Printer.h"

#include "AccountSystem.h"
#include "AccountSystemParser.h"


class Router {
public:
    Router();
    Reader * buildReader();
    Printer * buildPrinter();

    AccountSystemParser * accountSystemParser;
    void setAccountSystemController(AccountSystemController * accountSystemController);
    void route();
    void chooseDirection(nlohmann::json j);
    std::mutex readMutex;
    std::mutex printMutex;
    std::mutex accountSystemMutex;


private:
    std::queue<nlohmann::json> toDeliver;
    std::queue<nlohmann::json> toPrint;

    std::queue<nlohmann::json> toAccountSystem;
    AccountSystemController * accountSystemController_;

};


#endif //ANOTHER_CARD_GAME_ACG_ROUTER_H
