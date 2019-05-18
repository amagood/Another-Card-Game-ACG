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

class Router {
public:
    Router();
    Reader * buildReader();
    Printer * buildPrinter();
    std::mutex readMutex;
    std::mutex printMutex;

private:
    std::queue<nlohmann::json> toDeliver;
    std::queue<nlohmann::json> toPrint;
};


#endif //ANOTHER_CARD_GAME_ACG_ROUTER_H
