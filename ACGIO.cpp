//
// Created by jacky on 2019/5/18.
//

#include "ACGIO.h"

#include <thread>

ACGIO::ACGIO() {
    printer = new Printer(printDeque_, printMutex);
    reader = new Reader(readDeque_, readMutex);
}

void ACGIO::insertMsg(nlohmann::json j) {
    printMutex.lock();
    printDeque_.push_back(j);
    printMutex.unlock();
}
void ACGIO::print() {
    printer->print();
}
void ACGIO::read() {
    reader->read();
}
void ACGIO::passToRoute(){
    while(true) {
        readMutex.lock();
        if (readDeque_.empty()) {
            printMutex.unlock();
        }
        else {
            nlohmann::json j = readDeque_.front();
            readDeque_.pop_front();
            printMutex.unlock();
            routeMutex->lock();
            routeDeque_->push_back(j);
            routeMutex->unlock();
        }
    }
};
void ACGIO::setRouter(Router * router1) {
    router = router1;
    routeMutex = &(router->routeMutex_);
    routeDeque_ = &(router->routeDeque_);
}
void ACGIO::route() {
    router->run();
}
void ACGIO::run() {
    std::thread read_thread(&ACGIO::read, this);
    std::thread print_thread(&ACGIO::print, this);
    std::thread route_thread(&ACGIO::route, this);
    std::thread pass_to_route_thread(&ACGIO::passToRoute, this);

    read_thread.join();
    print_thread.join();
    route_thread.join();
    pass_to_route_thread.join();
}