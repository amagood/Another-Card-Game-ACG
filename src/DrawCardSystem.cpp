//
// Created by jacky on 2019-05-17.
//
#include "DrawCardSystem.h"

DrawCardSystem::DrawCardSystem() {
    cardInfoSystem = CardInfoSystem();
    cardpools = cardInfoSystem.getCardPool();
}

uint32_t DrawCardSystem::drawCard() {
    std::uniform_int_distribution<int> distribution(0, cardpools.size()-1);
    return cardpools.at(distribution(rd));
}
