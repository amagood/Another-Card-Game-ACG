//
// Created by jacky on 2019/4/21.
//

#include "Router.h"

#include <queue>

#include <chrono>
#include <thread>
#include <iostream>


#include "nlohmann/json.hpp"

#include "Reader.h"
#include "Printer.h"


#define SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
using std::cout;
Router::Router() {
    accountSystemParser = new AccountSystemParser();
    accountSystemParser->setIOQueue(toAccountSystem, accountSystemMutex);
}
void Router::setAccountSystemController(AccountSystemController *accountSystemController) {
    accountSystemController_ = accountSystemController;
}
void Router::route() {
    while(true) {
        readMutex.lock();
        if(toDeliver.empty()) {
            readMutex.unlock();
            continue;
        } else {
            nlohmann::json j = toDeliver.front();
            toDeliver.pop();
            readMutex.unlock();
            chooseDirection(j);
        }
    }
}
void Router::chooseDirection(nlohmann::json j) {
    if(j["data"]["eventType"] == "accountSystem") {
        accountSystemMutex.lock();
        toAccountSystem.push(j);
        accountSystemMutex.unlock();
    } else {
        cout << j;
    }
    // TODO add other direction
}


Printer* Router::buildPrinter() {
    return new Printer(toPrint, printMutex);
}
Reader* Router::buildReader() {
//    return new Reader(toDeliver, readMutex);
    return nullptr;
}