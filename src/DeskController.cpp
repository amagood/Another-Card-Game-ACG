//
// Created by vbscript on 2019/5/26.
//

#include "DeskController.h"

void DeskController::run(U32vec &player1, U32vec &player2){
    CardFactory CF_;//Deck method & Cards factory
    while(!player1.empty()){
        plate_.playerDeck[0].pushCard(CF_.createCard(player1[0]));
        player1.erase(player1.begin());
    }
    while(!player2.empty()){
        plate_.playerDeck[1].pushCard(CF_.createCard(player2[0]));
        player1.erase(player2.begin());
    }
    initPlate();
    //ready for server json to play game
}

nlohmann::json DeskController::getJson(nlohmann::json json_){
    if(plate_.whosTurn != json_["data"]["myPlayerId"]){ //if change player
        //draw card(change people)
        plate_.whosTurn = json_["data"]["myPlayerId"];
        desk_.draw(plate_);
        //package and return
        return package();
    }

    if(json_["data"]["useOrAttack"]=="useCard") //UseCard
    {
        Card * Main;
        if((int)json_["data"]["selectedCardId"]%10){
            Main= plate_.BF[plate_.whosTurn][(int)json_["data"]["selectedCardId"]/10];
        }
        else{
            Main= plate_.hand[plate_.whosTurn][(int)json_["data"]["selectedCardId"]/10];
        }

        if((int)json_["data"]["targetCardId"]/10 < 2){
            int side = (plate_.whosTurn + (int)json_["data"]["targetCardId"]%10) % 2;
            Card * target = plate_.BF[side][(int)json_["data"]["targetCardId"]/10];
            desk_.playerMovement(plate_, json_["data"]["useOrAttack"], Main, target);
        }
        else{ //全場或頭
            if((int)json_["data"]["targetCardId"]/10 == 3){ //頭
                //實體化生物(Hero)
                Hero *temp = new Hero();
                //設定血量
                temp->setHp(plate_.playerHp[!plate_.whosTurn]);
                //playerMovement
                desk_.playerMovement(plate_, json_["data"]["useOrAttack"], Main, temp);
                //寫回血量
                plate_.playerHp[!plate_.whosTurn] = temp->getHp();
            }
            else{
                desk_.playerMovement(plate_, json_["data"]["useOrAttack"], Main);
            }
        }
    }
    else{
        throw "json_error!!!";
    }
    return package();
}

void DeskController::initPlate(){
    //起手五張
    for(int i=0;i<5;i++){
       plate_.hand[0].push_back(plate_.playerDeck[0].popDeck(-1));
       plate_.hand[1].push_back(plate_.playerDeck[1].popDeck(-1));
    }
    //set player HP
    plate_.playerHp[0] = 30;
    plate_.playerHp[1] = 30;
    //set Turn
    plate_.whosTurn = -1;
}

int DeskController::winer_and_endgame() {
    return  (plate_.playerHp[0] > 0) && (plate_.playerHp[1] <= 0) ? 0 : (plate_.playerHp[0] <= 0) && (plate_.playerHp[1] > 0) ? 1 : -1;
}

nlohmann::json DeskController::Card2Json(Card *temp){
    nlohmann::json tmp;
    tmp["CardId"] = temp->getId();
    tmp["CardCost"] = temp->getMp();
    tmp["CardHealth"] = temp->getHp();
    tmp["CardATK"] = temp->getAtk();
    tmp["attributes"] = temp->getAttributes(); //???
    return tmp;
}

nlohmann::json DeskController::package(){ //auto plate -> json
    nlohmann::json Pack;
    std::vector <nlohmann::json> output;

    for(int j=0;j<2;j++){
        output.clear();
        for(int i=0;i < ((int)plate_.hand[j].size());i++)
            output.push_back(Card2Json(plate_.hand[j][i]));
        Pack["userHand" + std::to_string(j)] = output;
        output.clear();
        for(int i=0;i < ((int)plate_.BF[j].size());i++)
            output.push_back(Card2Json(plate_.BF[j][i]));
        Pack["userField" + std::to_string(j)] = output;
    }
    Pack["HP0"] = plate_.playerHp[0];
    Pack["HP1"] = plate_.playerHp[1];
    return Pack;
}

