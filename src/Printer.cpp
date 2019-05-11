//
// Created by jacky on 2019/4/21.
//

#include "Printer.h"

#include <iostream>

#include "nlohmann/json.hpp"
Printer::Printer(std::deque<nlohmann::json> &toPrintDeque, std::mutex &p) {
    toPrintDeque_ = &toPrintDeque;
    queueMutex = &p;
}

void Printer::print() {
    while (true) {
        queueMutex->lock();
        if(!toPrintDeque_->empty()) {

            nlohmann::json json_ = toPrintDeque_->front();
            toPrintDeque_->pop_front();
            std::cout << json_.dump();
        }
        queueMutex->unlock();
    }
}