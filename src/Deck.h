#ifndef ANOTHER_CARD_GAME_ACG_READER_H
#define ANOTHER_CARD_GAME_ACG_READER_H

#include <Card.h>
#include <iostream>
#include <vector>
#include <ctime>
#include "nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

class Deck
{
public:
    void pushCard(Card C);
    void pushCard(json JSON);

    vector<Card> searchCards(int id);
    //-1 search by type, others by id

    vector<Card> getDeck();
    //取得整副牌

    Card popDeck(int index);
    //-1 抽一張牌, others just pop by index

    Card &getIndexCards(int num, int mode = 0, int sieve = -1);
    //取得Card reference, mode=0 (random抽取), mode=1 (從牌堆最前面), mode=-1 (從牌堆最後面), sieve=-1 所有牌,others 只有那種type的牌

    int size();

    void deckShuffler();

private:
    void Init();

    vector<Card> deckLinkList;
};

#endif //ANOTHER_CARD_GAME_ACG_READER_H