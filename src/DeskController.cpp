//
// Created by vbscript on 2019/5/26.
//

#include "DeskController.h"

nlohmann::json DeskController::run(U32vec &player1, U32vec &player2){
    error("Desk_init");
    CardFactory CF_;//Deck method & Cards factory
    while(!player1.empty()){
        plate_.playerDeck[0].pushCard(CF_.createCard(player1[0]));
        player1.erase(player1.begin());
    }
    plate_.BF[0].push_back(CF_.createCard(0));
    plate_.BF[0][0]->setHp(1);
    while(!player2.empty()){
        plate_.playerDeck[1].pushCard(CF_.createCard(player2[0]));
        player2.erase(player2.begin());
    }
    plate_.BF[1].push_back(CF_.createCard(0));
    plate_.BF[1][0]->setHp(1);
    initPlate();
    timer = 0;
    MpTemp = 1;
    desk_.draw(plate_);
    return package();
    //ready for server json to play game
}

nlohmann::json DeskController::getJson(nlohmann::json json_){

    /*
    if(plate_.whosTurn != (int)json_["myPlayerId"]) { //if change player
        error("people change " + std::to_string(plate_.whosTurn) + " to " + std::to_string((int)json_["myPlayerId"]));
        if (plate_.playerDeck[0].size() && plate_.playerDeck[1].size()) { // 不要抽光牌組啊~
            //error("draw card");
            plate_.whosTurn = json_["myPlayerId"];
            desk_.draw(plate_);
            for (int i = 0; i < 20; i++)
                plate_.CanAttack[i] = 0;
            plate_.Mp++;
            //package and return
            return package();
        } else {
            plate_.playerDeck[0].size() ? plate_.BF[1][0]->setMp(0) : plate_.BF[0][0]->setMp(0);
        }
    }
    */
    std::string _str = json_["useOrAttack"];
    if((int)json_["myPlayerId"] != plate_.whosTurn || ( _str == "None")){
        error("not u're turn!!!");
        return package();
    }

    if((int)json_["changeSideTag"]){
        error("people change " + std::to_string(plate_.whosTurn) + " to " + std::to_string(!plate_.whosTurn));
        if (plate_.playerDeck[0].size() && plate_.playerDeck[1].size()) { // 不要抽光牌組啊~
            //error("draw card");
            plate_.whosTurn = !plate_.whosTurn;
            desk_.draw(plate_);
            for (int i = 0; i < 20; i++)
                plate_.CanAttack[i] = 0;
            timer++;
            if(timer % 2 == 0) MpTemp++;
            plate_.Mp = MpTemp;

        } else {
            plate_.playerDeck[0].size() ? plate_.BF[1][0]->setMp(0) : plate_.BF[0][0]->setMp(0);
        }
        return package();
    }

    // if mp ok~
    int selected_index = (int)json_["selectedCardId"]%10;
    int want_Mp = (int)json_["selectedCardId"]/10 ? plate_.BF[plate_.whosTurn][selected_index]->getMp(): plate_.hand[plate_.whosTurn][selected_index]->getMp();
    _str = json_["useOrAttack"];
    if(plate_.Mp >=  want_Mp || "attack" == _str){
        plate_.Mp -= want_Mp;

        error("analysis Main");
        Card * Main;
        if((int)json_["selectedCardId"]/10){ //場上
            if(plate_.CanAttack[selected_index]){ //被冰凍
                return error_output("warning", "can't Attack");
            }
            else{//可以動
                Main = plate_.BF[plate_.whosTurn].at(selected_index);
                plate_.CanAttack[selected_index] = 1; // 打過了
            }
        }
        else{//手上
            int tmp = plate_.hand[plate_.whosTurn][selected_index]->getId();
            if((tmp/100 == 0) && ((std::string)json_["useOrAttack"]) == "attack"){//在手上打屁?
                return error_output("warning", "Minion on u're hand");
            }
            else{
                Main = plate_.hand[plate_.whosTurn].at(selected_index);
            }
        }

        //決定對象
        error("analysis target");
        Card * target;
        int target_index = (int)json_["targetCardId"]/10;
        std::string _str = json_["useOrAttack"];
        if( plate_.hand[plate_.whosTurn][selected_index]->getId() < 100 && _str == "use") {
            //是手下 and use~ 需要特殊處理!!
            plate_.CanAttack[plate_.BF[plate_.whosTurn].size()] = 1; // 剛招喚不能動
            plate_.BF[plate_.whosTurn].push_back(plate_.hand[plate_.whosTurn][selected_index]);
            plate_.hand[plate_.whosTurn].erase(plate_.hand[plate_.whosTurn].begin()+selected_index);
            desk_.playerMovement(plate_, json_["useOrAttack"], Main);

        }
        else{
            if(target_index < 2){//檯面
                int side = (plate_.whosTurn + target_index) % 2;
                int tmp = (int)json_["targetCardId"];
                target = plate_.BF[side][tmp%10];
                desk_.playerMovement(plate_, json_["useOrAttack"], Main, target);
            }
            else{ //全場
                desk_.playerMovement(plate_, json_["useOrAttack"], Main);
            }
        }
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
    //set Turn
    plate_.whosTurn = rand() % 2;
}

int DeskController::winer_and_endgame() {
    if( plate_.BF[1][0]->getHp() <= 0 || plate_.BF[0][0]->getHp() <= 0){
        if(plate_.BF[0][0]->getHp()<= 0) return 1;
        if(plate_.BF[1][0]->getHp()<= 0) return 0;
    }
    else{
        return -1;
    }
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
        for(int i=0;i < ((int)plate_.BF[j].size());i++) // 頭放在0
            output.push_back(Card2Json(plate_.BF[j][i]));
        Pack["userField" + std::to_string(j)] = output;
    }
    Pack["HP0"] = plate_.BF[0].front()->getHp();
    Pack["HP1"] = plate_.BF[1].front()->getHp();
    Pack["Mp"] = MpTemp;
    Pack["EndGame"] = winer_and_endgame() < 0 ? 1:0;
    Pack["whosTurn"] = plate_.whosTurn;
    //error(Pack);
    return Pack;
}

nlohmann::json DeskController::error_output(std::string type, std::string message){
    nlohmann::json output;
    output["eventype"] = "dialog";
    output["type"] = type;
    output["message"] = message;
    return output;
}

