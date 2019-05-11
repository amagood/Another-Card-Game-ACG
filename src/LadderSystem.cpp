//
// Created by jacky on 2019/4/22.
//

#include "LadderSystem.h"

void LadderSystem::join(Account *account) {
    int ladder_point = account->getLadderPoint();
    std::string id = account->getName();
    int u_num = account->getUniqueNumber();
    participant.push_back(new LadderPlayer(u_num, id, ladder_point));
}
void LadderSystem::leave(int remove_id) {
    int index = -1;
    for (int i = 0; i < participant.size(); i++) {
        if (participant.at(i)->u_id_ == remove_id) {
            index = i;
        }
    }
    if (index == -1) {
        return;
    }
    else {
        participant.erase(participant.begin() + index);
    }

}

LadderLevel LadderCalculate::get_level(int point) {

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
    // No enough participant
    if (participant.size() < 2) {
        return ;
    }

    // FIXME the code is dirty, should be fixed in the future
    int index1 = 0;
    int point1 = participant.at(0)->point_;
    int lastgame1 = participant.at(0)->Last_game;
    int index2 = 1;
    int point2 = participant.at(1)->point_;

    for (int i = 2; i < participant.size(); i++) {
        if(participant.at(i)->Last_game == lastgame1) {
            continue;
        } else if (abs(participant.at(i)->point_ - point1) < abs(point2 - point1))  {
            index2 = i;
            point2 = participant.at(i)->point_;
        }
    }
    // TODO create game
    // use index1 and index2 id to create game

}

