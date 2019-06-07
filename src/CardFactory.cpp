//
// Created by jacky on 2019/5/22.
//

#include "CardFactory.h"
#include "cards.h"
#include "CardInfoSystem.h"
#include "debug.h"
#define creator(id, class_, t) static CreatorImpl<class_> t; createTable.insert({id, &t})
CardFactory::CardFactory()
{
    creator(0, Hero, hero);
    creator(1, Card001, card001);
    creator(2, Card002, card002);
    creator(3, Card003, card003);
    creator(4, Card004, card004);
    creator(5, Card005, card005);
    creator(6, Card006, card006);
    creator(7, Card007, card007);
    creator(8, Card008, card008);
    creator(9, Card009, card009);
    creator(10, Card010, card010);
    creator(11, Card011, card011);
    creator(12, Card012, card012);
    creator(13, Card013, card013);

    creator(101, Card101, card101);
    creator(102, Card102, card102);
    creator(103, Card103, card103);
    creator(104, Card104, card104);
    creator(105, Card105, card105);
    creator(106, Card106, card106);
    creator(107, Card107, card107);
    creator(108, Card108, card108);
    creator(109, Card109, card109);
    creator(110, Card110, card110);
    creator(111, Card111, card111);
    creator(112, Card112, card112);
    creator(113, Card113, card113);
    creator(114, Card114, card114);
    creator(115, Card115, card115);
    creator(116, Card116, card116);
    creator(117, Card117, card117);
    creator(118, Card118, card118);

    creator(201, Card201, card201);
    creator(202, Card202, card202);
}

Card *CardFactory::createCard(int cardId)
{

    if (createTable.count(cardId) != 0) {
        Card * card = createTable.at(cardId)->create();
        cardInfoSystem.setCard(card, cardId);
        return card;
    }
    error("Return NullPtr for no this cardId");
    return nullptr;
}