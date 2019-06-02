//
// Created by jacky on 2019/6/3.
//

#ifndef ANOTHER_CARD_GAME_ACG_USEFULCALLS_H
#define ANOTHER_CARD_GAME_ACG_USEFULCALLS_H

#include <nlohmann/json.hpp>

class CardInfoSystem;
class UsefulCalls {
public:
    UsefulCalls();
    nlohmann::json run(nlohmann::json j);
    CardInfoSystem * cardInfoSystem;
};


#endif //ANOTHER_CARD_GAME_ACG_USEFULCALLS_H
