#ifndef AMAGOOD_DESK_H
#define AMAGOOD_DESK_H

class Desk
{
private:
    int hp0,hp1;
    ///declare:
    /**
        p0 deck
        p1 deck

        p0 hand
        p1 hand
    */
public:
    Desk();
    ~Desk();

    Card draw(int num);

    void playerMovement(int playerId);


};
#endif // AMAGOOD_DESK_CPP
