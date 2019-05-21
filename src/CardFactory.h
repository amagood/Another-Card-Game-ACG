//
// Created by jacky on 2019/5/22.
//

#ifndef ANOTHER_CARD_GAME_ACG_CARDFACTORY_H
#define ANOTHER_CARD_GAME_ACG_CARDFACTORY_H

#include <cards.h>
#include <set>

class CardFactory;

class CardIdType {
    friend CardFactory;
    std::set<uint32_t> minionIds;
    std::set<uint32_t> weaponIds;
    std::set<uint32_t> spellIds;
    CardIdType() {
        minionIds.insert(0);
        minionIds.insert(1);
    }

};

class CardFactory {
    CardIdType * types;
public:
    CardFactory();
    Card * createCard(int cardId);
};


#endif //ANOTHER_CARD_GAME_ACG_CARDFACTORY_H
