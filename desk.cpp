#include "desk.h"
#include <stdlib.h>
#include <time.h>
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
Desk::Desk(Deck deck0, Deck deck1, String n0, String n1)
{
    isEnd = false;
    winLose = -1;
    name0 = n0;
    name1 = n1;
    playerDeck.at(0) = deck0;
    playerDeck.at(1) = deck1;
    hp.at(0) = maxHp;
    hp.at(1) = maxHp;


    ///who go first?
    srand(time(0));
    int nowPlayer = rand()%2;

    ///first draw 3
    draw(3,nowPlayer);
    ///second draw 4
    draw(4,nowPlayer);
    /// give lucky coin to second player    (NOT DONE YET)


    while(!isEnd())
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
