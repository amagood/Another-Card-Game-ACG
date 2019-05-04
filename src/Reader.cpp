//
// Created by jacky on 2019/4/21.
//

#include "Reader.h"

#include <iostream>
#include <string>
#include <mutex>
#include <deque>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

Reader::Reader(std::deque<nlohmann::json> &toDeliver, std::mutex &mut)
{
    toDeliverQueue = &toDeliver;
    queueMutex = &mut;
}

void Reader::read()
{
    std::string line;
    while (std::getline(std::cin, line))
    {
        json json_ = json::parse(line);
        queueMutex->lock();
        toDeliverQueue->push(json_);
        queueMutex->unlock();
    }
}

json Reader::popJson(string type, int id)
{
    queueMutex->lock();
    for (deque<json>::iterator i = toDeliverQueue->begin(); i != toDeliverQueue->end(); i++)
    {
        if (j["data"]["eventType"] == type && j["userId"] == id)
        {
            json json_ = *i;
            toDeliverQueue->erase(i);
            queueMutex->unlock();
            return json_;
        }
    }
    queueMutex->unlock();
}