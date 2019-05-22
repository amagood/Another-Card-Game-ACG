//
// Created by jacky on 2019/5/22.
//

#include "CardFactory.h"

CardFactory::CardFactory() {
    types = new CardIdType();
}

Card* CardFactory::createCard(int cardId) {
    if(types->minionIds.find(cardId) != types->minionIds.end()) {
        // minionType
    } else if (types->spellIds.find(cardId) != types->spellIds.end()) {
        // spellIdsType
    } else if (types->weaponIds.find(cardId) != types->weaponIds.end()) {
        //
    }
    return nullptr;
}