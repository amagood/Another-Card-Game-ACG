//
// Created by jacky on 2019/5/22.
//

#include "CardFactory.h"
#include "cards.h"
#include "CardInfoSystem.h"
#include "debug.h"

CardFactory::CardFactory()
{
    types = new CardIdType();
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
    else
    {
        error("null card");
        return nullptr;
    }
}