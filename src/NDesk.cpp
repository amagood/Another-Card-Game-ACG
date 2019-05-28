//
// Created by vbscript on 2019/5/26.
//

#include "NDesk.h"

NDesk::NDesk(){}

void NDesk::playerMovement(plate &state, Deck &deck, std::string action, Card *Main, Card *target){
    if(action == "use"){
        ((Spell*)Main)->use();//指定目標???
    }
    else if(action == "attack"){
        ((Minion*)Main)->attack(*((Minion*)target));
    }
    //refreshBF(state); 刷新檯面
}

void NDesk::refreshBF(plate &state){ //TODO Card 夠聰明知道啥時要做啥時不做?! 或是提供屬性讓我判斷要不要呼叫
    use(state.BF, state.whosTurn);
    use(state.hand, state.whosTurn);
}

void NDesk::use(std::vector<Card *> Cards[2],bool t) {
    for(int n=0;n<2;t = !t, n++)
        for(int i=0;i< Cards[t].size();i++){
            //TODO
        }
}

void NDesk::draw(plate &state, Deck &deck){
    state.hand[state.whosTurn].push_back(deck.popDeck());
}
