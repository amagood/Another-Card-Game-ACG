//
// Created by vbscript on 2019/5/26.
//

#ifndef ANOTHER_CARD_GAME_ACG_NDESK_H
#define ANOTHER_CARD_GAME_ACG_NDESK_H

#include <vector>
#include "cards.h"

class NDesk{ //執行指令
public:

    void playerMovement(Plate &state, std::string action, Card *Main, Card *target = NULL);

    void refreshBF(Plate &state);

    void draw(Plate &state);
private:

    void use(std::vector<Card *> Cards[2],bool t);
};

#endif //ANOTHER_CARD_GAME_ACG_NDESK_H
