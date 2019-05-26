//
// Created by vbscript on 2019/5/26.
//

#ifndef ANOTHER_CARD_GAME_ACG_DESKCONTROLLER_H
#define ANOTHER_CARD_GAME_ACG_DESKCONTROLLER_H

#include <vector>
#include "cards.h"
#include "Deck.h"
#include "NDesk.h"
#include <ctime>
#include <nlohmann/json.hpp>

class DeskController { //分析json 傳遞指令
public:
    DeskController(Deck &player1, Deck &player2);//先攻放 1,後攻放 2
    nlohmann::json getJson(nlohmann::json json_);
    int winer_and_endgame(); //return value = 0 還沒人贏, 1 贏家先攻者, -1 贏家後攻者(不支援平手)
private:
    void initPlate();
    nlohmann::json package();
    NDesk desk_;
    plate plate_;
    Deck PD[2];
};


#endif //ANOTHER_CARD_GAME_ACG_DESKCONTROLLER_H
