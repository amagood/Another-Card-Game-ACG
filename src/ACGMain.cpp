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
#include "AccountSystemController.h"
void ACGMain::acgio_run(){
    acgio->run();
}

void ACGMain::run() {
    std::thread io_thread(&ACGMain::acgio_run, this);
    io_thread.join();
}
ACGMain::ACGMain() {

    acgio = new ACGIO();
    router = new Router();
    accountSystemController = new AccountSystemController();
    router->setAccountSystems(accountSystemController);
    acgio->setRouter(router);


}
