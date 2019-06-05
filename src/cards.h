#ifndef CARDS_H_AMAGOOD
#define CARDS_H_AMAGOOD

#include <string>
#include <plate.h>

/**
     struct plate
    {
        std::vector<Card *> BF[2],hand[2]; //battlefield
        int playerHp[2];
        bool whosTurn;
    };
 */


class Card
{
protected:
    int atk,hp,mp,id;
	std::string name;
    std::string attrib;
    Plate *holdPlate;
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

	virtual void use(Plate *p,Card *target)=0;
    virtual ~Card(){};

};

class Weapon : public Card
{
public:
	Weapon();
    void usedOnce();
    virtual void use(Plate *p,Card *target);
    virtual ~Weapon();
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
	Hero() =default;
    void use(Plate *p,Card *target){};
};

class Card001 final : public Minion
{
public:
	Card001() = default;
    void use(Plate *p,Card *target){};
};

class Card002 final : public Minion
{
public:
    Card002() = default;
    void use(Plate *p,Card *target);
};

class Card003 final : public Minion
{
public:
    Card003() = default;
    void use(Plate *p,Card *target);
};

class Card004 final : public Minion
{
public:
    Card004() = default;
    void use(Plate *p,Card *target);
};

/////////////////spells/////////////////

class Card101 final : public Spell
{
public:
    Card101() = default;
    void use(Plate *p,Card *target);

};
class Card102 final : public Spell
{
public:
    Card102() = default;
    void use(Plate *p,Card *target);

};
class Card103 final : public Spell
{
public:
    Card103() = default;
    void use(Plate *p,Card *target);

};
class Card104 final : public Spell
{
public:
    Card104() = default;
    void use(Plate *p,Card *target);

};
class Card105 final : public Spell
{
public:
    Card105() = default;
    void use(Plate *p,Card *target);

};
class Card106 final : public Spell
{
public:
    Card106() = default;
    void use(Plate *p,Card *target);

};
class Card107 final : public Spell
{
public:
    Card107() = default;
    void use(Plate *p,Card *target);

};
class Card108 final : public Spell
{
public:
    Card108() = default;
    void use(Plate *p,Card *target);

};

/////////////////weapons/////////////////
class Card201 final : public Weapon
{
public:
    Card201() = default;
};
#endif // CARDS_H_AMAGOOD

