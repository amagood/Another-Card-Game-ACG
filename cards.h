#ifndef CARDS_H_AMAGOOD
#define CARDS_H_AMAGOOD

#include <string>
class Card
{
private:
    int atk,hp,mp,id;
	String name;
	String attrib;
public:
    Card(int attack,int healthPoint,int mannaRequired,int ID,String Name);
    void setAtk(int attack);
    void setHp(int healthPoint);
    void setMp(int mannaRequired);
    void setAttributes(String s);
	
    void atkIncrease(int i);
    void hpIncrease(int i);

    int getAtk();
    int getHp();
    int getMp();
	int getId();
	string getName();
	string getAttributes();
	
	virtual void use()=0;

};

class Weapon : public Card
{
public:
    void usedOnce();
};

class Spell : public Card
{

};

class Minion : public Card
{
public:
    void attack(Minion &target);
};

//////////////////Cards: ////////////////////////////

//////////////////Minions: //////////////////////////
class Hero : public Minion
{
	Hero();
};


#endif // CARDS_H_AMAGOOD

