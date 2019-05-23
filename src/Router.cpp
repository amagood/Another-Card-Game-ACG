//
// Created by jacky on 2019/4/21.
//

#include "Router.h"

#include <chrono>
#include <thread>
#include <iostream>


#define SLEEP(ms) std::this_thread::sleep_for(std::chrono::milliseconds(ms))
using std::cout;
Router::Router(){
    accountSystemParser = new AccountSystemParser(toAccountSystem, accountSystemMutex);
}
void Router::setAccountSystems(AccountSystemController *accountSystemController) {
    accountSystemParser->setAccountSystemController(accountSystemController);
}

void Router::route() {
    while(true) {
        routeMutex_.lock();
        if(routeDeque_.empty()) {
            routeMutex_.unlock();
        } else {
            nlohmann::json j = routeDeque_.front();
            routeDeque_.pop_front();
            routeMutex_.unlock();
            chooseDirection(j);
        }
    }
}
void Router::chooseDirection(nlohmann::json j) {
    if(j["data"]["eventType"] == "accountSystem") {
        accountSystemMutex.lock();
        toAccountSystem.push_back(j);
        accountSystemMutex.unlock();
    } else {
        // TODO add other direction

   }
}

void Router::run() {
    route();
}