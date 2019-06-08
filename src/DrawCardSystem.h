//
// Created by jacky on 2019-05-17.
//

#ifndef ANOTHER_CARD_GAME_ACG_DRAWCARDSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_DRAWCARDSYSTEM_H

#include <random>
#include <CardInfoSystem.h>

class DrawCardSystem {
public:
    DrawCardSystem();
    uint32_t drawCard();
    U32vec drawCards(uint32_t num);
private:
    U32vec cardpools;
    U32vec drawAbleCardpools;
    std::default_random_engine rd;
    CardInfoSystem cardInfoSystem;
};


#endif //ANOTHER_CARD_GAME_ACG_DRAWCARDSYSTEM_H
