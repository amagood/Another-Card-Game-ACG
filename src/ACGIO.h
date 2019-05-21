//
// Created by jacky on 2019/5/18.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACGIO_H
#define ANOTHER_CARD_GAME_ACG_ACGIO_H

#include <nlohmann/json.hpp>

#include "Reader.h"
#include "Sender.h"
#include "Printer.h"
#include "Router.h"

class ACGIO {
    Reader * reader;
    std::deque<nlohmann::json> printDeque_;
    std::mutex printMutex;
    std::deque<nlohmann::json> readDeque_;
    std::mutex readMutex;
    std::mutex *routeMutex;
    std::deque<nlohmann::json> *routeDeque_;
    Printer * printer;
    Router * router;
    void read();
    void print();
    void route();
    void passToRoute();
public:
    ACGIO();
    void setRouter(Router *);
    void insertMsg(nlohmann::json j);
    void run();
};


#endif //ANOTHER_CARD_GAME_ACG_ACGIO_H
