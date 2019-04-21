//
// Created by jacky on 2019/4/21.
//

#include "Printer.h"

#include <iostream>

#include "nlohmann/json.hpp"
Printer::Printer(std::queue<nlohmann::json> &toPrint, std::mutex &mut) {
    toPrintQueue = &toPrint;
    queueMutex = &mut;
}

void Printer::print() {
    while (true) {
        queueMutex->lock();
        if(!toPrintQueue->empty()) {

            nlohmann::json json_ = toPrintQueue->front();
            toPrintQueue->pop();
            std::cout << json_.dump();
        }
        queueMutex->unlock();
    }
}