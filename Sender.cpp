//
// Created by jacky on 2019/4/21.
//

#include "Sender.h"

#include <iostream>
#include <mutex>
#include <deque>

#include "nlohmann/json.hpp"
using json = nlohmann::json;

Sender::Sender(std::deque<nlohmann::json> &toTransfer, std::mutex &mut)
{
    toTransferQueue = &toTransfer;
    queueMutex = &mut;
}

void Sender::send()
{
    while (toTransferQueue->size())
    {
        queueMutex->lock();
        std::cout << toTransferQueue->front() << endl;
        toTransferQueue->pop_fornt();
        queueMutex->unlock();
    }
}

void Sender::pushJson(json json_)
{
    queueMutex->lock();
    toTransferQueue->push(json_);
    queueMutex->unlock();
}