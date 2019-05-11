#ifndef CARDS_H_AMAGOOD
#define CARDS_H_AMAGOOD

#include <string>
class Card
{
private:
    int atk,hp,mp,id;
	std::string name;
    std::string attrib;
public:
    Card(int attack, int healthPoint,int mannaRequired, int ID, std::string Name);
    void setAtk(int attack);
    void setHp(int healthPoint);
    void setMp(int mannaRequired);
    void setAttributes(std::string s);
	
    void atkIncrease(int i);
    void hpIncrease(int i);

    int getAtk();
    int getHp();
    int getMp();
	int getId();
    std::string getName();
    std::string getAttributes();
	Card *copy();
	
	

};

class Weapon : public Card
{
public:
    void usedOnce();
	virtual void use()=0;
};

class Spell : public Card
{
public:
    virtual void use()=0;
};

class Minion : public Card
{
public:
    void attack(Minion &target);
	virtual void use()=0;
};

//////////////////Cards: ////////////////////////////

//////////////////Minions: //////////////////////////
class Hero final : public Minion
{
	Hero();
};

class Card001 final : public Minion
{
	Card001();
};
#endif // CARDS_H_AMAGOOD

