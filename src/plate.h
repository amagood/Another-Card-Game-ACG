//
// Created by amagood on 2019/6/1.
//

#ifndef ANOTHER_CARD_GAME_ACG_PLATE_H
#define ANOTHER_CARD_GAME_ACG_PLATE_H

#include <vector>
#include "Deck.h"
class Card;
struct Plate
{
    std::vector<Card *> BF[2],hand[2]; //battlefield
    Deck playerDeck[2];
    int playerHp[2];
    int whosTurn;
    int GodHpAtk;
};

#endif //ANOTHER_CARD_GAME_ACG_PLATE_H
