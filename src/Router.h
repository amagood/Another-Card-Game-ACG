//
// Created by jacky on 2019/4/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_ROUTER_H
#define ANOTHER_CARD_GAME_ACG_ROUTER_H

#include <nlohmann/json.hpp>

class AccountSystem;
class AccountSystemController;
class ArenaController;
class UsefulCalls;
class Router {
public:
    Router();
    nlohmann::json run(nlohmann::json& j);
    void end();
private:
    AccountSystemController * accountSystemController;
    ArenaController * arenaController;
    AccountSystem * accountSystem;
    UsefulCalls * usefulCalls;
};
#endif //ANOTHER_CARD_GAME_ACG_ROUTER_H
