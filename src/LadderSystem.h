//
// Created by jacky on 2019/4/22.
//

#ifndef ANOTHER_CARD_GAME_ACG_LADDERSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_LADDERSYSTEM_H

#include "AccountSystem.h"

enum LadderLevel{
    COPPER = 0, SILVER = 1, GOLD = 2, DIAMOND = 3, GREAT_MASTER = 4
};
class LadderSystem;
class LadderCalculate {
    public:
    static LadderLevel get_level(int point);
};

class LadderPlayer {
public:
    uint32_t u_id_;
    std::string id_;
    int point_;
    int Last_game;
    LadderLevel level;

    LadderPlayer(uint32_t u_id, std::string name, int point) : u_id_(u_id), id_(name), point_(point) {
        level = LadderCalculate::get_level(point);
    }
};

class LadderSystem {
public:

    LadderSystem(){};
    std::vector<LadderPlayer *> participant;
    void join(Account *account);
    void match();
    void leave(uint32_t remove_id);
private:

};


#endif //ANOTHER_CARD_GAME_ACG_LADDERSYSTEM_H
