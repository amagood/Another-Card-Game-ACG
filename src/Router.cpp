//
// Created by jacky on 2019/4/21.
//
#include "Router.h"

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "ArenaController.h"
#include "AccountSystemController.h"
#include "debug.h"
#include "usefulCalls.h"
Router::Router() {
    accountSystem = new AccountSystem();
    accountSystemController = new AccountSystemController(accountSystem);
    arenaController = new ArenaController(accountSystem);
    usefulCalls = new UsefulCalls();
}
void Router::end() {
    accountSystem->saveAccounts();
}
nlohmann::json Router::run(nlohmann::json &j) {
    if (j["data"]["eventType"] == "accountSystem") {
        try {
            return accountSystemController->run(j);
        } catch (std::exception &e) {
            error("accountSystem but I don't know what happen");
            return nlohmann::json({});
        }
    } else if (j["data"]["eventType"] == "room" || j["data"]["eventType"] == "desk") {
        error("goto arena");
        try {
            j["data"] = arenaController->run(j["data"])["data"];
            return j;
        } catch (std::exception &e){
            error("arenaError but I don't know what happen");
            return nlohmann::json({});
        }

    } else if (j["data"]["eventType"] == "usefulcalls" ) {
        error("goto usefulCalls");
        try {
            j = usefulCalls->run(j);
            return j;
        } catch (std::exception &e) {
            error("Error for usefulCalls");
            return nlohmann::json({});
        }
    } else {
        error("empty");
        return nlohmann::json({});
    }
}
