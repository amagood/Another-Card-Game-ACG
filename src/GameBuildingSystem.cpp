//
// Created by jacky on 2019/5/22.
//

#include "GameBuildingSystem.h"


GameBuildingSystem::GameBuildingSystem() {
    cardFactory = new CardFactory();
    cardInfoSystem = new CardInfoSystem();
}
Deck GameBuildingSystem::U32VecToDeck(U32vec cardIDs) {
    Deck deck;
    for (uint32_t id: cardIDs) {
        Card * card = cardFactory->createCard(id);
        deck.pushCard(card);
    }
    return deck;
}