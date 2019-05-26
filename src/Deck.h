#ifndef ANOTHER_CARD_GAME_ACG_DECK_H
#define ANOTHER_CARD_GAME_ACG_DECK_H

#include <vector>
#include <ctime>
#include <nlohmann/json.hpp>
#include "cards.h"

class Deck
{
public:
    Deck(){};
    void pushCard(Card *C);
    void pushCard();

    //-1 search by type, others by id

    std::vector<Card *> getDeck();
    //取得整副牌

    Card *popDeck(int index = -1);
    //-1 抽一張牌, others just pop by index

    Card *getIndexCards(int num, int mode, std::type_info sieve);
    Card *getIndexCards(int num, int mode);
    //取得Card address, mode=0 (random抽取), mode=1 (從牌堆最前面), mode=-1 (從牌堆最後面), sieve=-1 所有牌,others 只有那種type的牌

    int size();

    void deckShuffler();

    ~Deck();
private:
    void Init();

    std::vector<Card *> deckLinkList;
};

#endif //ANOTHER_CARD_GAME_ACG_DECK_H