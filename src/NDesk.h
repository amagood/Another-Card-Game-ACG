//
// Created by vbscript on 2019/5/26.
//

#ifndef ANOTHER_CARD_GAME_ACG_NDESK_H
#define ANOTHER_CARD_GAME_ACG_NDESK_H

#include <vector>
#include "cards.h"
#include "Deck.h"
struct plate
{
    std::vector<Card *> BF[2],hand[2]; //battlefield
    int playerHp[2];
    bool whosTurn;
};

class NDesk{ //執行指令
public:
    NDesk();//constructor(....)

    void playerMovement(plate &state, Deck &deck, std::string action, Card *Main, Card *target = NULL);

    void refreshBF(plate &state);

    void draw(plate &state, Deck &deck);
private:

    void use(std::vector<Card *> Cards[2],bool t);
};

#endif //ANOTHER_CARD_GAME_ACG_NDESK_H
