//
// Created by vbscript on 2019/5/26.
//

#include "DeskController.h"
#include "debug.h"

void DeskController::run(U32vec &player1, U32vec &player2){
    error("Desk_init");
    CardFactory CF_;//Deck method & Cards factory
    while(!player1.empty()){
        plate_.playerDeck[0].pushCard(CF_.createCard(player1[0]));
        player1.erase(player1.begin());
    }
    while(!player2.empty()){
        plate_.playerDeck[1].pushCard(CF_.createCard(player2[0]));
        player2.erase(player2.begin());
    }
    initPlate();
    //ready for server json to play game
}

nlohmann::json DeskController::getJson(nlohmann::json json_){
    error("DC eat~!!!");
    if(plate_.whosTurn != (int)json_["myPlayerId"]){ //if change player
        //draw card(change people)
        error("draw card");
        plate_.whosTurn = json_["myPlayerId"];
        desk_.draw(plate_);
        plate_.Mp++;
        //package and return
        return package();
    }


    // if mp ok~
    int selected_index = (int)json_["selectedCardId"]%10;
    int want_Mp = (int)json_["selectedCardId"]/10 ? plate_.BF[plate_.whosTurn][selected_index]->getMp(): plate_.hand[plate_.whosTurn][selected_index]->getMp();
    if(plate_.Mp >=  want_Mp){
        error("Mp OK~");
        plate_.Mp -= want_Mp; // !!??
        error("Main?");

        Card * Main;
        if((int)json_["selectedCardId"]/10){ //場上
            if(plate_.CanAttack[selected_index]){ //被冰凍
                return error_output("warning", "so cold~");
            }
            else{//可以動
                Main = plate_.BF[plate_.whosTurn].at(selected_index);
                plate_.CanAttack[selected_index] = 1;
            }
        }
        else{//手上
            int tmp = plate_.hand[plate_.whosTurn][selected_index]->getId();
            if((tmp/100 == 0) && ((std::string)json_["useOrAttack"]) == "Attack"){//在手上打屁?
                return error_output("warning", "Minion on u're hand");
            }
            else{
                Main = plate_.hand[plate_.whosTurn].at(selected_index);
            }
        }

        //決定對象
        error("target?");
        Card * target;
        int target_index = (int)json_["targetCardId"]/10;
        if(plate_.hand[plate_.whosTurn][selected_index]->getId()/100 && json_["useOrAttack"] != "use") { // not Minion
            if(target_index < 2){//檯面

                int side = (plate_.whosTurn + (int)json_["targetCardId"]%10) % 2;
                target = plate_.BF[side].at(target_index);
                desk_.playerMovement(plate_, json_["useOrAttack"], Main, target);
            }
            else{ //全場或頭
                if(target_index == 3){ //頭
                    //實體化生物(Hero)
                    Hero *temp = new Hero();
                    //設定血量
                    temp->setHp(plate_.playerHp[!plate_.whosTurn]);
                    //playerMovement
                    desk_.playerMovement(plate_, json_["useOrAttack"], Main, temp);
                    //寫回血量
                    plate_.playerHp[!plate_.whosTurn] = temp->getHp();
                }
                else{
                    desk_.playerMovement(plate_, json_["useOrAttack"], Main);
                }
            }
        }
        else{//是手下~ 需要特殊處理!!
            plate_.BF[plate_.whosTurn].push_back(plate_.hand[plate_.whosTurn][selected_index]);
            plate_.hand[plate_.whosTurn].erase(plate_.hand[plate_.whosTurn].begin()+selected_index);
            //plate_.hand[plate_.whosTurn][selected_index] = nullptr;
            desk_.playerMovement(plate_, json_["useOrAttack"], Main);
        }
        error("package return");
        return package();
    }
    else{
        error("warning");
        return error_output("warning", "Mp not enought");
    }

}

void DeskController::initPlate(){
    //起手五張
    for(int i=0;i<5;i++){
       plate_.hand[0].push_back(plate_.playerDeck[0].popDeck());
       plate_.hand[1].push_back(plate_.playerDeck[1].popDeck());
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
    if(temp == NULL){
        error("NO~~~~!!!");
    }
    else{
        tmp["CardId"] = temp->getId();
        tmp["CardCost"] = temp->getMp();
        tmp["CardHealth"] = temp->getHp();
        tmp["CardATK"] = temp->getAtk();
        tmp["attributes"] = temp->getAttributes(); //???
    }
    return tmp;
}

nlohmann::json DeskController::package(){ //auto plate -> json
    error("packing");
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
    Pack["Mp"] = plate_.Mp;
    error(Pack);
    return Pack;
}

nlohmann::json DeskController::error_output(std::string type, std::string message){
    nlohmann::json output;
    output["type"] = type;
    output["message"] = message;
    return output;
}

