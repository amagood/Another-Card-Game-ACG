//
// Created by jacky on 2019/4/21.
//

#include "Sender.h"

#include <iostream>

using json = nlohmann::json;

Sender::Sender(std::deque<nlohmann::json> &toTransfer, std::mutex &mut)
{
    //toTransferQueue = toTransfer;
    //queueMutex = &mut;
}

void Sender::send()
{
    while (toTransferQueue.size())
    {
        //queueMutex->lock();
        std::cout << toTransferQueue.front() << std::endl;
        toTransferQueue.pop_front();
        //queueMutex->unlock();
    }
}

void Sender::pushJson(json json_)
{
    //queueMutex->lock();
    toTransferQueue.push_back(json_);
    //queueMutex->unlock();
}