#ifndef AMAGOOD_DESK_H
#define AMAGOOD_DESK_H

class Desk
{
private:
    int hp0,hp1;
    bool isEnd;
    int winLose; //0->p0 wins 1-> p1 wins
    ///declare:
    /**
        p0 deck
        p1 deck

        p0 hand
        p1 hand
    */
public:
    Desk(Deck deck0, Deck deck1, String name0, String name1);
    ~Desk();

    Card draw(int num);

    void playerMovement(int playerId);

    bool isEnd();
    int getWinPlayer();
};
#endif // AMAGOOD_DESK_CPP