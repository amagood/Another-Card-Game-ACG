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
    Card *card = nullptr;
    if (types->minionIds.find(cardId) != types->minionIds.end())
    {
        // minionType
        // 0 - 99
        if (cardId == 1)
        {
            card = new Card001();
        }
        else if (cardId == 2)
        {
            card = new Card002();
        }
        else if (cardId == 3)
        {
            card = new Card003();
        }
        else if (cardId == 4)
        {
            card = new Card004();
        }
        else if (cardId == 5)
        {
            card = new Card005();
        }
        else if (cardId == 6)
        {
            card = new Card006();
        }
        else if (cardId == 7)
        {
            card = new Card007();
        }
        else if (cardId == 8)
        {
            card = new Card008();
        }
        else if (cardId == 9)
        {
            card = new Card009();
        }
        else if (cardId == 10)
        {
            card = new Card010();
        }
        else if (cardId == 11)
        {
            card = new Card011();
        }
        else if (cardId == 12)
        {
            card = new Card012();
        }
        else if (cardId == 13)
        {
            card = new Card013();
        }


    }
    else if (types->spellIds.find(cardId) != types->spellIds.end())
    {
        // spellIdsType
        if (cardId == 101)
        {
            card = new Card101();
        }
        else if (cardId == 102)
        {
            card = new Card102();
        }
        else if (cardId == 103)
        {
            card = new Card103();
        }
        else if (cardId == 104)
        {
            card = new Card104();
        }
        else if (cardId == 105)
        {
            card = new Card105();
        }
        else if (cardId == 106)
        {
            card = new Card106();
        }
        else if (cardId == 107)
        {
            card = new Card107();
        }
        else if (cardId == 108)
        {
            card = new Card108();
        }
        else if (cardId == 109)
        {
            card = new Card109();
        }
        else if (cardId == 110)
        {
            card = new Card110();
        }
        else if (cardId == 111)
        {
            card = new Card111();
        }
        else if (cardId == 112)
        {
            card = new Card112();
        }
        else if (cardId == 113)
        {
            card = new Card113();
        }
        else if (cardId == 114)
        {
            card = new Card114();
        }
        else if (cardId == 115)
        {
            card = new Card115();
        }
        else if (cardId == 116)
        {
            card = new Card116();
        }
        else if (cardId == 117)
        {
            card = new Card117();
        }
        else if (cardId == 118)
        {
            card = new Card118();
        }
    }
    else if (types->weaponIds.find(cardId) != types->weaponIds.end())
    {
        if (cardId == 201)
        {
            card = new Card201();
        }
        else if (cardId == 202)
        {
            card = new Card202();
        }
    }
    if (card != nullptr)
    {
        cardInfoSystem.setCard(card, cardId);
        return card;
    }
    error("Return NullPtr for no this cardId");
    return nullptr;
}