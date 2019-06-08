//
// Created by jacky on 2019-05-17.
//
#include "DrawCardSystem.h"

DrawCardSystem::DrawCardSystem() {
    cardInfoSystem = CardInfoSystem();
    cardpools = cardInfoSystem.getCardPool();
    for(uint32_t cardId: cardpools) {
        if(cardId!=0) {
            drawAbleCardpools.push_back(cardId);
        }
    }
}

uint32_t DrawCardSystem::drawCard() {
    std::uniform_int_distribution<int> distribution(0, drawAbleCardpools.size()-1);
    return drawAbleCardpools.at(distribution(rd));
}

U32vec DrawCardSystem::drawCards(uint32_t num) {
    U32vec cardlist;
    while(num--) {
        cardlist.push_back(drawCard());
    }
    return cardlist;
}
