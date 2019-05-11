    //
// Created by jacky on 2019/4/20.
//

#include "ACGMain.h"

#include <mutex>
#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>

#include "Printer.h"
#include "Reader.h"
#include "Router.h"


ACGMain::ACGMain() {
    router = new Router();
    //reader = router->buildReader();
    printer = router->buildPrinter();

    accountSystemController = new AccountSystemController();
    router->setAccountSystemController(accountSystemController);

//    ladderSystem = new LadderSystem();
}

void ACGMain::print() {
    printer->print();
}
void ACGMain::read() {
    //reader->read();
}

void ACGMain::route() {
    router->route();
}
void ACGMain::run() {
    //std::thread read_thread(&ACGMain::read, this);
    std::thread print_thread(&ACGMain::print, this);
    std::thread route_thread(&ACGMain::route, this);
    //read_thread.join();
    print_thread.join();
    route_thread.join();

}