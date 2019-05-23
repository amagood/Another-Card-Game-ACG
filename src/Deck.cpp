#include "Deck.h"

#include <iostream>
#include <vector>

#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

int Deck::size()
{
    return deckLinkList.size();
}

void Deck::pushCard(Card *C)
{
    deckLinkList.push_back(C);
}
void Deck::pushCard(json JSON) //
{
    //Card Card_;

    //Deck::pushCard(Card_);
}

//-1 search by type, others by id

vector<Card *> Deck::getDeck()
{
    return this->deckLinkList;
}
//取得整副牌

Card *Deck::popDeck(int index = -1)
{
    if (index == -1)
    {
        Card *card_ = deckLinkList[-1];
        deckLinkList.pop_back();
        return card_;
    }
    else
    {
        delete *(deckLinkList.begin() + index);
        deckLinkList.erase(deckLinkList.begin() + index);
    }
    return nullptr;
}
//-1 抽一張牌, others just pop by index

Card *Deck::getIndexCards(int num, int mode, std::type_info sieve)
{
    if (mode) // mode => 1 or -1
    {
        uint32_t i;
        for (i = (num > 0 ? deckLinkList.size() - 1 : 0); (num > 0 ? i >= 0 : i < deckLinkList.size()) && num; i += ((num > 0) - (num < 0)))
        {
            if (sieve == typeid(*deckLinkList[i]))
            {
                num += ((num < 0) - (num> 0));
            }
        }
        return deckLinkList[i];
    }
    else // mode => 0
    {
        int temp = rand() % deckLinkList.size();
        // TODO fixed
        while (sieve == typeid(*deckLinkList[temp]))
        {
            temp = rand() % deckLinkList.size();
        }

        return deckLinkList[temp];
    }
}

Card *Deck::getIndexCards(int num, int mode)
{
    if (mode) // mode => 1 or -1
    {
        uint32_t i;
        for (i = (num > 0 ? deckLinkList.size() - 1 : 0); (num > 0 ? i >= 0 : i < deckLinkList.size()) && num; i += ((num > 0) - (num < 0)))
        {
            num += ((num<0) - (num> 0));
        }
        return deckLinkList[i];
    }
    else // mode => 0
    {
        int temp = rand() % deckLinkList.size();
        return deckLinkList[temp];
    }
}

//取得Card reference, mode=0 (random抽取), mode=1 (從牌堆最前面), mode=-1 (從牌堆最後面), sieve=-1 所有牌,others 只有那種type的牌

void Deck::deckShuffler()
{
    Deck::Init();
    for (uint32_t i = 0; i < deckLinkList.size(); i++)
        swap(deckLinkList[i], deckLinkList[i + rand() % (deckLinkList.size() - i)]);
}

void Deck::Init()
{
    srand(time(NULL));
}

Deck::~Deck()
{
    for (uint32_t i = 0; i < deckLinkList.size(); i++)  {
        delete (deckLinkList[i]);
    }
}