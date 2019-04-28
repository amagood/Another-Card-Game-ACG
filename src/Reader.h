//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_READER_H
#define ANOTHER_CARD_GAME_ACG_READER_H

#include <string>
#include <deque>
#include <mutex>

#include "nlohmann/json.hpp"
using json = nlohmann::json;
class Reader
{
public:
    Reader(std::deque<nlohmann::json> &toDeliver, std::mutex &mutex);
    void read();
    json popJson(int type, int id);

private:
    std::deque<nlohmann::json> *toDeliverQueue;
    std::mutex *queueMutex;
};

#endif //ANOTHER_CARD_GAME_ACG_READER_H
