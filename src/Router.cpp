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
        return accountSystemController->run(j);
    } else if (j["data"]["eventType"] == "room" || j["data"]["eventType"] == "desk") {
        error("goto arena");
        j["data"] = arenaController->run(j["data"])["data"];
        return j;
    } else if (j["data"]["eventType"] == "usefulcalls" ) {
        error("goto usefulCalls");
        j = usefulCalls->run(j);
        return j;
    } else {
        error("empty");
        return nlohmann::json();
    }
}
