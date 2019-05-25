//
// Created by jacky on 2019/4/21.
//

#include "Router.h"

#include "AccountSystem.h"
#include "ArenaController.h"
#include "AccountSystemController.h"


Router::Router() {
    accountSystem = new AccountSystem();
    accountSystemController = new AccountSystemController(accountSystem);
    arenaController = new ArenaController(accountSystem);
};

nlohmann::json Router::run(nlohmann::json &j) {
    if (j["data"]["eventType"] == "accountSystem") {
        accountSystemController->run(j);
    } else {
        arenaController->run(j);
    }

};
