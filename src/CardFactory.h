//
// Created by jacky on 2019/5/22.
//

#ifndef ANOTHER_CARD_GAME_ACG_CARDFACTORY_H
#define ANOTHER_CARD_GAME_ACG_CARDFACTORY_H

#include "cards.h"
#include "ACGType.h"
#include "CardInfoSystem.h"
class CardFactory;

class Creator
{
public:
    virtual Card* create() = 0;
};
template <class T>
class CreatorImpl : public Creator
{
public:
    virtual Card* create() { return new T; }
};

class CardFactory {
    CardInfoSystem cardInfoSystem;
    std::map<uint32_t, Creator *> createTable;

public:
    CardFactory();
    Card * createCard(int cardId);
};


#endif //ANOTHER_CARD_GAME_ACG_CARDFACTORY_H
