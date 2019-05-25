//
// Created by jacky on 2019/5/26.
//

#ifndef ANOTHER_CARD_GAME_ACG_ARENACONTROLLER_H
#define ANOTHER_CARD_GAME_ACG_ARENACONTROLLER_H

#include <nlohmann/json.hpp>
class AccountSystem;
class ArenaController {
public:
    ArenaController(AccountSystem *);
    nlohmann::json run(nlohmann::json &);
};


#endif //ANOTHER_CARD_GAME_ACG_ARENACONTROLLER_H
