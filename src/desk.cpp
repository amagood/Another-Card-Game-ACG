#include "desk.h"

#include <cstdint>
#include <queue>
#include <typeinfo>

#include <nlohmann/json.hpp>

=#include "Deck.h"


int otherPlayer(int nowPlayer)
{
    return (nowPlayer+1)%2;
}
nlohmann::json Desk::outputSites()
{
	using namespace std;
	vector<nlohmann::json> siteJson0,siteJson1,handJson0,handJson1;
	auto tmp=site.at(0).getDeck();
	for(auto i : tmp)
	{
		nlohmann::json tmp2;
		tmp2["cardUuid"]=(uint32_t)i->getId();
		tmp2["attack"]= i->getId();
		tmp2["hp"]=i->getHp();
		tmp2["attributes"]=i->getAttributes();

		siteJson0.push_back(tmp2);
	}
	tmp=site.at(1).getDeck();
	for(auto i : tmp)
	{
		nlohmann::json tmp2;
		tmp2["cardUuid"]=(uint32_t)i->getId();
		tmp2["attack"]= i->getId();
		tmp2["hp"]=i->getHp();
		tmp2["attributes"]=i->getAttributes();

		siteJson1.push_back(tmp2);
	}
	tmp=hand.at(0).getDeck();
	for(auto i : tmp)
	{
		nlohmann::json tmp2;

		tmp2["cardUuid"]=(uint32_t)i->getId();
		tmp2["attack"]= i->getId();
		tmp2["hp"]=i->getHp();
		tmp2["attributes"]=i->getAttributes();

		handJson0.push_back(tmp2);
	}
	tmp=hand.at(1).getDeck();
	for(auto i : tmp)
	{
		nlohmann::json tmp2;
		tmp2["cardUuid"]=(uint32_t)i->getId();
		tmp2["attack"]= i->getId();
		tmp2["hp"]=i->getHp();
		tmp2["attributes"]=i->getAttributes();

		handJson1.push_back(tmp2);
	}


	nlohmann::json outputJson;
	outputJson["time"]=(time_t) time(NULL);
	outputJson["type"]="gameLogicEngineMessage";
	outputJson["userId"]=(uint32_t)myId;
	outputJson["data"]["eventType"]="deskState";
	outputJson["data"]["userHand0"]=handJson0;
	outputJson["data"]["userHand1"]=handJson1;
	outputJson["data"]["userField0"]=siteJson0;
	outputJson["data"]["userField1"]=siteJson1;

	return outputJson;
}
void Desk::draw(int num,int targetPlayer)
{
    for(int i=0;i<num;i++)
        hand.at(targetPlayer).pushCard(playerDeck.at(targetPlayer).popDeck(-1));
}

bool Desk::checkDead(int playerId)
{
	int indexi=0;
	for(auto i : site.at(playerId).getDeck())
	{
		if(i->getHp() <= 0)//die
		{
			if(indexi == 0)
			{
				winLose = playerId;
				end_ = true;
				return true;
			}
            site.at(playerId).popDeck(indexi);

		}
		indexi++;
	}

	playerId=otherPlayer(playerId);

	indexi=0;
	for(auto i : site.at(playerId).getDeck())
	{
		if(i->getHp()<=0)//die
		{
			if(indexi==0)
			{
				winLose=playerId;
				end_=true;
				return true;
			}
            site.at(playerId).popDeck(indexi);

		}
		indexi++;
	}
	return false;
}

bool Desk::playerMovement(int playerId)
{
    using namespace std;
    bool endMovement = false;

    while(!endMovement)
    {
        nlohmann::json inputAction;

        ///Eat JSON
        inputAction = ip->popJson("desk",myId);

		/**
		json A;
		A["data"]["deskId"]
		*/


        if(inputAction["data"]["useOrAttack"]=="useCard" && inputAction["data"]["useOrAttack"]=="use")        ///Use Card
        {
            ///push index'th card from the hand to site
            site.at(playerId).pushCard( hand.at(playerId).popDeck(inputAction["data"]["selectedCardId"]));   //Not done for magic cards pop
            // FIXME please QAQ
            //site.at(playerId).getIndexCards(0,-1)/*getLastCard*/.use();
			if(strcmp(typeid(site.at(playerId).getIndexCards(0,-1)).name(),"5Spell"))  ///if it is a Spell then pop after used from site
				site.at(playerId).popDeck(site.at(playerId).size()-1);
        }
        else if(inputAction["data"]["useOrAttack"]=="useCard" && inputAction["data"]["useOrAttack"]=="attack")  ///Attack
        {
            Minion * me, *target;
            me = (Minion*)(site.at(playerId).getIndexCards(inputAction["data"]["selectedCardId"],1));
            target = (Minion*)(site.at(otherPlayer(playerId)).getIndexCards(inputAction["data"]["targetPlayerId"],1));
            me->attack(*target);
        }
        else       ///End
        {
            endMovement = true;
        }

		op->pushJson(outputSites());

		if(checkDead(playerId))
			return true;
    }
	return false;

}
Desk::Desk(Reader *input, Sender *output, int deskId,
           U32vec cardID0s, U32vec cardID1s, std::string n0, std::string n1)  //constructor
{
    using namespace std;

    myId = deskId;
    ip=input;
    op=output;

    end_ = false;
    winLose = -1;
    name0 = n0;
    name1 = n1;
    playerDeck.push_back(gameBuildingSystem.U32VecToDeck(cardID0s));
    playerDeck.push_back(gameBuildingSystem.U32VecToDeck(cardID1s));
    site.push_back(Deck());
    site.push_back(Deck());
    hand.push_back(Deck());
    hand.push_back(Deck());

    end_ = false;


	site.at(0).pushCard(new Hero);
	site.at(1).pushCard(new Hero);


    ///who go first?
    srand(time(0));
    int nowPlayer = rand()%2;

    ///first draw 3
    draw(3,nowPlayer);
    ///second draw 4
    draw(4,nowPlayer);
    /// give lucky coin to second player    (NOT DONE YET)


    while(!end_)
    {
        /// first player's round
        draw(1,nowPlayer);
		if(playerMovement(nowPlayer))
			return;

        nowPlayer = otherPlayer(nowPlayer);
        ///second player's round
        draw(1,nowPlayer);
        if(playerMovement(nowPlayer))
			return;
        nowPlayer = otherPlayer(nowPlayer);

    }



}
bool Desk::isEnd()
{
	return end_;
}
int Desk::getWinPlayer()
{
	return winLose;
}
