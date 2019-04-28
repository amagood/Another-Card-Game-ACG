//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_PRINTER_H
#define ANOTHER_CARD_GAME_ACG_PRINTER_H

#include <string>
#include <queue>
#include <mutex>

#include "../lib/nlohmann/json.hpp"
using json = nlohmann::json;
class Printer
{
public:
    Printer(std::queue<nlohmann::json> &toPrintQueue, std::mutex &p);

    void print();

private:
    std::queue<nlohmann::json> *toPrintQueue;
    std::mutex *queueMutex;
};

#endif //ANOTHER_CARD_GAME_ACG_PRINTER_H
