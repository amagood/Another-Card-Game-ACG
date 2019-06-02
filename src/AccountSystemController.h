//
// Created by jacky on 2019-05-11.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H

#include <mutex>

#include "AccountSystem.h"
#include "DrawCardSystem.h"

class AccountSystemController {
    AccountSystem * accountSystem;
    DrawCardSystem * drawCardSystem;
public:
    AccountSystemController(AccountSystem *);
    nlohmann::json run(nlohmann::json &);
};

#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEMCONTROLLER_H
