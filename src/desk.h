#ifndef AMAGOOD_DESK_H
#define AMAGOOD_DESK_H
#include "Reader.h"
#include "Sender.h"
#include <vector>
#include <queue>
#include <nlohmann/json.hpp>

class Desk final
{
private:
    //std::vector<int> hp(2);
    static constexpr int myPopJsonType = 0;
    //int hp0,hp1;
    bool isEnd;
    int winLose; //0->p0 wins 1-> p1 wins
    int myId;
    std::vector<Deck> playerDeck(2),hand(2),site(2) /**site : myDesk*/;
    //Deck playerDeck1,playerDeck2,hand1,hand2;
    Reader *ip;
    Sender *op;
    string name0,name1;
	bool playerMovement(int playerId);
	bool checkDead(int playerId);
	nlohmann::json outputSites();
	
public:
    Desk(Reader *input,Sender *output,int deskId,Deck deck0, Deck deck1, string n0, string n1);
    ~Desk();

    Card draw(int num,int targetPlayer);

    

    bool isEnd();
    int getWinPlayer();
};
#endif // AMAGOOD_DESK_CPP
