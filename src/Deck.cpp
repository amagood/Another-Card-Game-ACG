#include <cards.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <nlohmann/json.hpp>
#include <Deck.h>
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
}
//-1 抽一張牌, others just pop by index

Card *Deck::getIndexCards(int num, int mode, int sieve)
{
    if (mode) // mode => 1 or -1
    {
        int i;
        for (i = (num > 0 ? deckLinkList.size() - 1 : 0); (num > 0 ? i >= 0 : i < deckLinkList.size()) && num; i += (num > 0 - num < 0))
        {
            if (sieve == -1)
            {
                num += (num<0 - num> 0);
            }
            // TODO fix getCardType
            /*
            else if (sieve == deckLinkList[i]->getCardType())
            {
                num += (num<0 - num> 0);
            }*/
        }
        return deckLinkList[i];
    }
    else // mode => 0
    {
        int temp = rand() % deckLinkList.size();
        // TODO fix
        /*
        while (sieve != deckLinkList[temp]->getCardType() && sieve != -1)
        {
            temp = rand() % deckLinkList.size();
        }*/

        return deckLinkList[temp];
    }
}
//取得Card reference, mode=0 (random抽取), mode=1 (從牌堆最前面), mode=-1 (從牌堆最後面), sieve=-1 所有牌,others 只有那種type的牌

void Deck::deckShuffler()
{
    Deck::Init();
    for (int i = 0; i < deckLinkList.size(); i++)
        swap(deckLinkList[i], deckLinkList[i + rand() % (deckLinkList.size() - i)]);
}

void Deck::Init()
{
    srand(time(NULL));
}

Deck::~Deck()
{
    for (int i = 0; i < deckLinkList.size(); i++)  delete (deckLinkList[i]);
}