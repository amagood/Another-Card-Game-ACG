#ifndef CARDS_H_AMAGOOD
#define CARDS_H_AMAGOOD

#include <string>

class Card
{
protected:
    int atk,hp,mp,id;
	std::string name;
    std::string attrib;
public:
    Card() = default;
    Card(int attack, int healthPoint,int mannaRequired, int ID, std::string Name);

    void setAtk(int attack);
    void setHp(int healthPoint);
    void setMp(int mannaRequired);
    void setAttributes(std::string s);
	void setId(int num);
	void setName(std::string s);

    void atkIncrease(int i);
    void hpIncrease(int i);

    int getAtk();
    int getHp();
    int getMp();
	int getId();
    std::string getName();
    std::string getAttributes();

	virtual void use()=0;
    virtual ~Card(){};

};

class Weapon : public Card
{
public:
	Weapon();
    void usedOnce();
    virtual ~Weapon(){};
};

class Spell : public Card
{
public:
	Spell();
    virtual ~Spell(){};
};

class Minion : public Card
{
public:
	Minion();

    void attack(Minion &target);
    virtual ~Minion(){};
};

//////////////////Cards: ////////////////////////////

//////////////////Minions: //////////////////////////
class Hero : public Minion
{
public:
	Hero();
	void use(){};
};

class Card001 final : public Minion
{
public:
	Card001();
	void use(){};
};
#endif // CARDS_H_AMAGOOD

