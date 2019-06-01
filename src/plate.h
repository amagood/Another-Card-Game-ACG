//
// Created by amagood on 2019/6/1.
//

#ifndef ANOTHER_CARD_GAME_ACG_PLATE_H
#define ANOTHER_CARD_GAME_ACG_PLATE_H

#include <vector>
class Card;

struct Plate
{
    std::vector<Card *> BF[2],hand[2]; //battlefield
    int playerHp[2];
    bool whosTurn;
};

#endif //ANOTHER_CARD_GAME_ACG_PLATE_H
