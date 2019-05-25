//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_READER_H
#define ANOTHER_CARD_GAME_ACG_READER_H

#include <nlohmann/json.hpp>
class Reader {
public:
    static nlohmann::json read();
};

#endif //ANOTHER_CARD_GAME_ACG_READER_H