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
    reader = router->buildReader();
    printer = router->buildPrinter();
    accountSystem = new AccountSystem();
}

void ACGMain::print() {
    printer->print();
}
void ACGMain::read() {
    reader->read();
}

void ACGMain::run() {
    std::thread read_thread(&ACGMain::read, this);
    std::thread print_thread(&ACGMain::print, this);
    read_thread.join();
    print_thread.join();
}