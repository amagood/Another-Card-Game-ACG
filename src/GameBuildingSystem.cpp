//
// Created by jacky on 2019/5/22.
//

#include "GameBuildingSystem.h"


GameBuildingSystem::GameBuildingSystem() {
    cardFactory = new CardFactory();
    cardInfoSystem = new CardInfoSystem();
}
Deck GameBuildingSystem::createDeck(U32vec cardlist) {
    Deck deck;
    for (uint32_t id: cardlist) {
        Card * card = cardFactory->createCard(id);
        deck.pushCard(card);
    }
    return deck;
}