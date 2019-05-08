#include "desk.h"
#include "src/Reader.h"
#include "src/Sender.h.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <string.h>
#include <time.h>
#include <typeinfo>
#include <queue>
#include "nlohmann/json.hpp"
///include deck
constexpr maxHp = 60;

int otherPlayer(int nowPlayer)
{
    return (nowPlayer+1)%2;
}

Card Desk::draw(int num,int targetPlayer)
{
    for(int i=0;i<num;i++)
        hand.at(targetPlayer).pushCard(playerDeck.at(targetPlayer).popDeck(-1));
}
void Desk::playerMovement(int playerId)
{
    using namespace std;
    bool endMovement = false;

    while(!endMovement)
    {
        nlohmann::json inputAction;

        ///Eat JSON
        inputAction = ip->popJson(myPopJsonType,myId);

		/**
		json A;
		A["data"]["deskId"]
		*/


        if(inputAction["data"]["useOrAttack"]=="useCard" && inputAction["data"]["useOrAttack"]=="use")        ///Use Card
        {
            ///push index'th card from the hand to site
            site.at(playerId).pushCard( hand.at(playerId).popDeck(inputAction["data"]["selectedCardId"]));   //Not done for magic cards pop
            site.at(playerId).getIndexCards(0,-1,-1)/*getLastCard*/.use();  
			if(strcmp(typeid(site.at(playerId).getIndexCards(0,-1,-1)).name(),"5Spell"))  ///if it is a Spell then pop after used from site
				site.at(playerId).popDeck(site.at(playerId).size()-1);
        }
        else if(inputAction["data"]["useOrAttack"]=="useCard" && inputAction["data"]["useOrAttack"]=="attack")  ///Attack
        {
            site.at(playerId).getIndexCards(inputAction["data"]["selectedCardId"],1,-1).attack(site.at(otherPlayer(playerId)).getIndexCards(inputAction["data"]["targetPlayerId"],1,-1));
        }
        else       ///End
        {
            endMovement = true;
        }

    }


}
Desk(Reader *input,Sender *output,int deskId,Deck deck0, Deck deck1, string n0, string n1);
{
    using namespace std;
    myId = deskId;
    ip=input;
    op=output;

    isEnd = false;
    winLose = -1;
    name0 = n0;
    name1 = n1;
    playerDeck.at(0) = deck0;
    playerDeck.at(1) = deck1;
    hp.at(0) = maxHp;
    hp.at(1) = maxHp;
    isEnd = false;

    ///who go first?
    srand(time(0));
    int nowPlayer = rand()%2;

    ///first draw 3
    draw(3,nowPlayer);
    ///second draw 4
    draw(4,nowPlayer);
    /// give lucky coin to second player    (NOT DONE YET)


    while(!isEnd)
    {
        /// first player's round
        draw(1,nowPlayer);
        playerMovement(nowPlayer);
        nowPlayer = otherPlayer(nowPlayer);
        ///second player's round
        draw(1,nowPlayer);
        playerMovement(nowPlayer);
        nowPlayer = otherPlayer(nowPlayer);

    }



}
