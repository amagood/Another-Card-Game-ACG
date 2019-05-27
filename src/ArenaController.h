#ifndef ANOTHER_CARD_GAME_ACG_ARENACONTROLLER_H
#define ANOTHER_CARD_GAME_ACG_ARENACONTROLLER_H

#include <iostream>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "Router.h"
#include "Arena.h"

class ArenaController
{
public:
    ArenaController(AccountSystem * acc) : account(acc) { arena = Arena(); }
    nlohmann::json run(nlohmann::json json);
private:
    AccountSystem * account;
    Arena arena;
};



#endif //ANOTHER_CARD_GAME_ACG_ARENACONTROLLER_H
