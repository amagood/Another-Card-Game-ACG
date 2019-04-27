//
// Created by jacky on 2019/4/22.
//

#ifndef ANOTHER_CARD_GAME_ACG_LADDERSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_LADDERSYSTEM_H

#include <vector>
#include <string>
#include "AccountSystem.h"

enum LEVEL{
    COPPER = 0, SILVER = 1, GOLD = 2, DIAMOND = 3, GREAT_MASTER = ,
};
class LadderPlayer {
    LadderPlayer(int u_id, std::string id, int point_) : u_id_(u_id), id_(id), point_(point){
        level = LadderSystem::get_level(point_);
    }
    int u_id_;
    std::string id_;
    int point_;
    int Last_game;
    LEVEL level;
};

class LadderSystem {
public:
    std::vector<LadderPlayer *> &participant;
    void join(Account *account);
    void match();
    LEVEL get_level(int point);
private:

};
void LadderSystem::join(Account *account) {
    int ladder_point = account->get_ladder_point();
    std:string id = account->get_name();
    int u_num = account->get_unique_num();
    participant.push_back(new LadderPlayer(u_num, id, ladder_point));
}
LEVEL LadderSystem::get_level(int point) {
    if (point < 2000) {
        return COPPER; // 0 - 1999
    } else if (point < 2500) {
        return SILVER; // 2000 - 2499
    } else if (point < 3000) {
        return GOLD;   // 2500 - 2999
    } else if (point < 3500) {
        return DIAMOND; // 3000 - 3499
    } else {
        return GREAT_MASTER;
    }
}


void LadderSystem::match() {
    // TODO

}

#endif //ANOTHER_CARD_GAME_ACG_LADDERSYSTEM_H
