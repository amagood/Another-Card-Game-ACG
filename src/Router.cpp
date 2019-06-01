//
// Created by jacky on 2019/4/21.
//
#define DEBUG
#include "Router.h"

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "ArenaController.h"
#include "AccountSystemController.h"
#include "debug.h"

Router::Router() {
    accountSystem = new AccountSystem();
    accountSystemController = new AccountSystemController(accountSystem);
    arenaController = new ArenaController(accountSystem);
}

nlohmann::json Router::run(nlohmann::json &j) {
    if (j["data"]["eventType"] == "accountSystem") {
        return accountSystemController->run(j);
    } else if (j["data"]["eventType"] == "room"){
        error("goto arena")
        return arenaController->run(j);
    } else {
        error("empty")
        return nlohmann::json();
    }
}
