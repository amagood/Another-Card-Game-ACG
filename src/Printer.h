//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_PRINTER_H
#define ANOTHER_CARD_GAME_ACG_PRINTER_H

#include <nlohmann/json.hpp>

class Printer {
public:
    static void print(nlohmann::json &j);
};

#endif //ANOTHER_CARD_GAME_ACG_PRINTER_H
