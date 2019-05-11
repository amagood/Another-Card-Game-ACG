#ifndef AMAGOOD_DESK_H
#define AMAGOOD_DESK_H
#include "Reader.h"
#include "Sender.h"
#include "Deck.h"
#include <vector>
#include <queue>
#include <nlohmann/json.hpp>

class Desk final
{
private:
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
    Desk(Reader *input,Sender *output,int deskId,Deck deck0, Deck deck1,
            std::string n0, std::string n1);
    ~Desk();

    Card draw(int num,int targetPlayer);

    

    bool isEnd();
    int getWinPlayer();
};
#endif // AMAGOOD_DESK_CPP
