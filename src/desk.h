#ifndef AMAGOOD_DESK_H
#define AMAGOOD_DESK_H

#include <nlohmann/json.hpp>

#include "ACGType.h"
#include "GameBuildingSystem.h"
#include "Reader.h"
#include "Sender.h"
#include "Deck.h"


class Desk final
{
private:
    GameBuildingSystem gameBuildingSystem;
    static constexpr int myPopJsonType = 0;
    bool end_;
    int winLose; //0->p0 wins 1-> p1 wins
    int myId;
    std::vector<Deck> playerDeck, hand, site /**site : myDesk*/;
    Reader *ip;
    Sender *op;
    std::string name0,name1;
    bool playerMovement(int playerId);
    bool checkDead(int playerId);
    nlohmann::json outputSites();

public:
    Desk(Reader *input, Sender *output, int deskId, U32vec cardID0s, U32vec cardID1s,
         std::string n0, std::string n1);
    ~Desk();

    void draw(int num,int targetPlayer);



    bool isEnd();
    int getWinPlayer();
};
#endif // AMAGOOD_DESK_CPP
