//
// Created by jacky on 2019-05-17.
//

#ifndef ANOTHER_CARD_GAME_ACG_DRAWCARDSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_DRAWCARDSYSTEM_H


#include <cstdint>
#include <vector>

class DrawCardSystem {
public:
    DrawCardSystem();
    uint32_t drawCard();
private:
    void load();
    std::vector<uint32_t> cardpools;
};


#endif //ANOTHER_CARD_GAME_ACG_DRAWCARDSYSTEM_H
