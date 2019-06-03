//
// Created by jacky on 2019/5/22.
//

#include "CardFactory.h"
#include "cards.h"
#include "CardInfoSystem.h"
CardFactory::CardFactory() {
    types = new CardIdType();
}

Card* CardFactory::createCard(int cardId) {
    Card * card = nullptr;
    if(types->minionIds.find(cardId) != types->minionIds.end()) {
        // minionType
        // 0 - 99
        if (cardId == 0) {
            card = new Hero();
        } else if (cardId == 1) {
            card =  new Card001();
        } else if(cardId == 2){
            card = new Card002();
        } else if (cardId == 3) {
            card = new Card003();
        }


    } else if (types->spellIds.find(cardId) != types->spellIds.end()) {
        // spellIdsType
    } else if (types->weaponIds.find(cardId) != types->weaponIds.end()) {
        if (cardId == 201) {
            card = new Card201();
        }
    }
    if (card != nullptr) {
        cardInfoSystem.setCard(card, cardId);
        return card;
    } else {
        return nullptr;
    }
}