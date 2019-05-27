    //
// Created by jacky on 2019/4/20.
//

#include "ACGMain.h"

#include <mutex>
#include <iostream>
#include <thread>

#include <nlohmann/json.hpp>

#include "Room.h"
#include "AccountSystem.h"
#include "AccountSystemController.h"

void ACGMain::acgio_run(){
    //acgio->run();
}

void ACGMain::run() {
    //std::thread io_thread(&ACGMain::acgio_run, this);
    //io_thread.join();
}
ACGMain::ACGMain() {
    Reader reader = Reader();
    Sender sender = Sender();
    std::thread tReader;
    std::thread tSender;

    AccountSystem accountSystem = AccountSystem();
    Arena arena = Arena(&reader, &sender, &accountSystem);
    /*acgio = new ACGIO();
    router = new Router();
    accountSystemController = new AccountSystemController();
    router->setAccountSystems(accountSystemController);
    acgio->setRouter(router);*/
}
