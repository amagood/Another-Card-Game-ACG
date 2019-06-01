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
#include "ACGType.h"
#include "CardFactory.h"
class DeskController { //分析json 傳遞指令
public:
    void run(U32vec &player1, U32vec &player2);//前端玩家與排組的順序要對應!!!
    nlohmann::json getJson(nlohmann::json json_);
    int winer_and_endgame(); //return value = 0 還沒人贏, 1 贏家先攻者, -1 贏家後攻者(不支援平手)
private:
    void initPlate();
    nlohmann::json package();
    nlohmann::json Card2Json(Card *temp);
    NDesk desk_;
    Plate plate_;
    Deck PD[2];
};
#endif //ANOTHER_CARD_GAME_ACG_DESKCONTROLLER_H