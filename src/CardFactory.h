//
// Created by jacky on 2019/5/22.
//

#ifndef ANOTHER_CARD_GAME_ACG_CARDFACTORY_H
#define ANOTHER_CARD_GAME_ACG_CARDFACTORY_H

#include "cards.h"
#include "ACGType.h"
#include "CardInfoSystem.h"
class CardFactory;

class CardIdType {
    friend CardFactory;
    U32set minionIds;
    U32set weaponIds;
    U32set spellIds;
    CardIdType() {
        minionIds.insert(0);
        minionIds.insert(1);
        minionIds.insert(2);
        minionIds.insert(3);
        minionIds.insert(4);
        weaponIds.insert(201);
    }

};

class CardFactory {
    CardIdType * types;
    CardInfoSystem cardInfoSystem;
public:
    CardFactory();
    Card * createCard(int cardId);
};


#endif //ANOTHER_CARD_GAME_ACG_CARDFACTORY_H
