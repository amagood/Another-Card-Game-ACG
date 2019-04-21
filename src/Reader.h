//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_READER_H
#define ANOTHER_CARD_GAME_ACG_READER_H

#include <string>
#include <queue>
#include <mutex>

#include "nlohmann/json.hpp"

class Reader {
public:
    Reader(std::queue<nlohmann::json> &toDeliver, std::mutex &mutex);
    void read();

private:
    std::queue<nlohmann::json> *toDeliverQueue;
    std::mutex *queueMutex;
};


#endif //ANOTHER_CARD_GAME_ACG_READER_H
