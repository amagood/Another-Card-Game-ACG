//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_PRINTER_H
#define ANOTHER_CARD_GAME_ACG_PRINTER_H

#include <mutex>
#include <deque>

#include <nlohmann/json.hpp>

class Printer {

public:
    Printer(std::deque<nlohmann::json> &toPrintDeque, std::mutex &p);

    void print();

private:
    std::deque<nlohmann::json> *toPrintDeque_;

    std::mutex * queueMutex;
};





#endif //ANOTHER_CARD_GAME_ACG_PRINTER_H
