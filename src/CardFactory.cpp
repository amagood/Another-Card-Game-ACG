//
// Created by jacky on 2019/5/22.
//

#include "CardFactory.h"
#include "cards.h"

CardFactory::CardFactory() {
    types = new CardIdType();
}

Card* CardFactory::createCard(int cardId) {
    if(types->minionIds.find(cardId) != types->minionIds.end()) {
        // minionType
        // 0 - 99
        if (cardId == 0) {
            return new Hero();
        } else if (cardId == 1) {
            return new Card001();
        } else if(cardId == 2){
            return new Card002();
        } else if (cardId == 3) {
            return new Card003();
        }


    } else if (types->spellIds.find(cardId) != types->spellIds.end()) {
        // spellIdsType
    } else if (types->weaponIds.find(cardId) != types->weaponIds.end()) {
        if (cardId == 201) {
            return new Card201();
        }
    }
    return nullptr;
}