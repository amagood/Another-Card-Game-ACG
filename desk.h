#ifndef AMAGOOD_DESK_H
#define AMAGOOD_DESK_H
#include <vector>
///include deck

class Desk
{
private:
    std::vector<int> hp(2);
    //int hp0,hp1;
    bool isEnd;
    int winLose; //0->p0 wins 1-> p1 wins
    std::vector<Deck> playerDeck(2),hand(2);
    //Deck playerDeck1,playerDeck2,hand1,hand2;

    string name0,name1;
public:
    Desk(Deck deck0, Deck deck1, string n0, string n1);
    ~Desk();

    Card draw(int num,int targetPlayer);

    void playerMovement(int playerId);

    bool isEnd();
    int getWinPlayer();
};
#endif // AMAGOOD_DESK_CPP
