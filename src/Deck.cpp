#include "Deck.h"
#include <ctime>
#include <random>

Deck::Deck(){
    head_ptr = 0;
    for(int i = 0;i < 1000;i++)
        deckLinkList[i];
}

int Deck::size()
{
    return head_ptr;
}

void Deck::pushCard(Card *C)
{
    deckLinkList[head_ptr++] = C;
}

Card *Deck::popDeck(int index)
{
    if (index == -1)
    {
        Card * Card_ = deckLinkList[head_ptr-1];
        deckLinkList[head_ptr-1] = NULL;
        head_ptr--;
        return Card_;
    }
    else
    {
        for(int i=index;i<head_ptr;i++)
            deckLinkList[i] = deckLinkList[i+1];
        head_ptr--;
    }
    return nullptr;
}



//-1 抽一張牌, others just pop by index
/*
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
*/
//取得Card reference, mode=0 (random抽取), mode=1 (從牌堆最前面), mode=-1 (從牌堆最後面), sieve=-1 所有牌,others 只有那種type的牌

void Deck::deckShuffler()
{
    Deck::Init();
    for (uint32_t i = 0; i < head_ptr; i++)
        std::swap(deckLinkList[i], deckLinkList[i + rand() % (head_ptr - i)]);
}
void Deck::Init(){
    srand(time(NULL));
}


Deck::~Deck()
{
    for (uint32_t i = 0; i < head_ptr; i++){//TODO
        delete (deckLinkList[i]);
    }
}