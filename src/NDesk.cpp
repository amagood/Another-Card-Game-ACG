//
// Created by vbscript on 2019/5/26.
//

#include "NDesk.h"

void NDesk::playerMovement(Plate &state, std::string action, Card *Main, Card *target){
    if(action == "use"){
        error(Main->getName() + " use " + (target == NULL ? "" : target->getName()));
        Main->use(&state,target);
    }
    else if(action == "attack"){
        error(Main->getName() + " Attack " + (target == NULL ? "" : target->getName()));
        ((Minion*)Main)->attack(*(Minion*)target);
    }
    refreshBF(state); //刷新檯面
}

void NDesk::refreshBF(Plate &state){
    for(int j=0;j < 2;j++){
        for(std::vector <Card *>::iterator i = state.BF[j].begin()+1;i != state.BF[j].end();i++){
            if((*i)->getHp()<=0){
                delete (*i);
                state.BF[j].erase(i--);
            }
        }
    }
    //use(state.BF, state.whosTurn);
    //use(state.hand, state.whosTurn);
}

void NDesk::use(std::vector<Card *> Cards[2],bool t) {
    for(int n=0;n<2;t = !t, n++)
        for(int i=0;i< ((int)Cards[t].size());i++){
            //No
        }
}

void NDesk::draw(Plate &state){
    error("player " + std::string(std::to_string(state.whosTurn)) + " draw a card");
    state.playerDeck[state.whosTurn].deckShuffler();
    state.hand[state.whosTurn].push_back(state.playerDeck[state.whosTurn].popDeck());
}
