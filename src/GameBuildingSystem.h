//
// Created by jacky on 2019/5/22.
//

#ifndef ANOTHER_CARD_GAME_ACG_GAMEBUILDINGSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_GAMEBUILDINGSYSTEM_H

#include "CardInfoSystem.h"
#include "CardFactory.h"
#include "Deck.h"
#include "ACGType.h"
class GameBuildingSystem {


    CardInfoSystem * cardInfoSystem= new CardInfoSystem();
    CardFactory * cardFactory = new CardFactory();
public:
    GameBuildingSystem();
    Deck createDeck(U32vec cardlist);

};


#endif //ANOTHER_CARD_GAME_ACG_GAMEBUILDINGSYSTEM_H
