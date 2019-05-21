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
private:
    U32vec cardpools;
    std::default_random_engine rd;
    CardInfoSystem cardInfoSystem;
};


#endif //ANOTHER_CARD_GAME_ACG_DRAWCARDSYSTEM_H
