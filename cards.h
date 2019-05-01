#ifndef CARDS_H_AMAGOOD
#define CARDS_H_AMAGOOD

class Card
{
private:
    int atk,hp,mp;
public:
    Card(int attack,int healthPoint,int mannaRequired);
    void setAtk(int attack);
    void setHp(int healthPoint);
    void setMp(int mannaRequired);

    void atkIncrease(int i);
    void hpIncrease(int i);

    int getAtk();
    int getHp();
    int getMp();

};

class Weapon : public Card
{
public:
    void usedOnce();
};

class Spell : public Card
{
public:
    virtual void magic()=0;
};

class Minion : public Card
{
public:
    void attack(Minion &target);
};

#endif // CARDS_H_AMAGOOD

