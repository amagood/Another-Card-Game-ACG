//
// Created by jacky on 2019/4/21.
//

#include "Reader.h"

#include <iostream>
#include <string>
#include <mutex>

#include "nlohmann/json.hpp"

Reader::Reader(std::queue<nlohmann::json> &toDeliver, std::mutex &mut) {
    toDeliverQueue = &toDeliver;
    queueMutex = &mut;
}


void Reader::read() {
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        nlohmann::json json_ = nlohmann::json::parse(line);
        queueMutex->lock();
        toDeliverQueue->push(json_);
        queueMutex->unlock();
    }
}