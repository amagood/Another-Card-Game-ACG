//
// Created by vbscript on 2019/5/26.
//

#include "NDesk.h"

void NDesk::playerMovement(Plate &state, std::string action, Card *Main, Card *target){
    if(action == "use"){
        ((Spell*)Main)->use(&state,target);
    }
    else if(action == "attack"){
        ((Minion*)Main)->attack(*((Minion*)target));
    }
    //refreshBF(state); No刷新檯面
}

void NDesk::refreshBF(Plate &state){
    use(state.BF, state.whosTurn);
    use(state.hand, state.whosTurn);
}

void NDesk::use(std::vector<Card *> Cards[2],bool t) {
    for(int n=0;n<2;t = !t, n++)
        for(int i=0;i< ((int)Cards[t].size());i++){
            //No
        }
}

void NDesk::draw(Plate &state){
    state.hand[state.whosTurn].push_back(state.playerDeck[state.whosTurn].popDeck());
}
