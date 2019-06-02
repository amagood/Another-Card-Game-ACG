//
// Created by jacky on 2019/5/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_CARDINFOSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_CARDINFOSYSTEM_H

#include <string>
#include <map>
#include "cards.h"
#include "ACGType.h"

struct InfoCard {
    int id;
    int hp;
    int mp;
    int atk;
    std::string name;
    std::string attribute;
};

class CardInfoSystem {

public:
    CardInfoSystem();
    InfoCard * getInfoCard(int id);
    int getHp(int id);
    int getMp(int id);
    int getAtk(int id);
    std::string getName(int id);
    std::string getAttribute(int id);
    U32vec getCardPool();
    void setCard(Card *, int id);
private:
    std::map<uint32_t , InfoCard> infoCards;
    U32vec cardlist;
    void load();

};


#endif //ANOTHER_CARD_GAME_ACG_CARDINFOSYSTEM_H
