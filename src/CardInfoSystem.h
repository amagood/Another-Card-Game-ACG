//
// Created by jacky on 2019/5/21.
//

#ifndef ANOTHER_CARD_GAME_ACG_CARDINFOSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_CARDINFOSYSTEM_H

#include <cstdint>

#include <string>
#include <vector>
#include <map>

#include "ACGType.h"
struct InfoCard {
    int id;
    int hp;
    int mp;
    int mp_cost;
    std::string name;
    std::string attribute;
};

class CardInfoSystem {
    std::map<uint32_t , InfoCard> infoCards;
    U32vec cardlist;
public:
    CardInfoSystem();
    void load();
    void show();
    InfoCard * getInfoCard(int id);
    int getHp(int id);
    int getMp(int id);
    int getMpCost(int id);
    std::string getName(int id);
    std::string getAttribute(int id);
};


#endif //ANOTHER_CARD_GAME_ACG_CARDINFOSYSTEM_H
