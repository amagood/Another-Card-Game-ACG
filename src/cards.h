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

    virtual void atkIncrease(int i);
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
    virtual void usedOnce();
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

    virtual void attack(Minion &target);
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
class Card005 final : public Minion
{
public:
    Card005() = default;
    void use(Plate *p,Card *target);
};
class Card006 final : public Minion
{
public:
    Card006() = default;
    void use(Plate *p,Card *target);
};
class Card007 final : public Minion
{
public:
    Card007() = default;
    void attack(Minion &target);
    void use(Plate *p,Card *target);
};
class Card008 final : public Minion
{
public:
    Card008() = default;
    void attack(Minion &target);
    void use(Plate *p,Card *target);
};
class Card009 final : public Minion
{
public:
    Card009() = default;
    void use(Plate *p,Card *target);
};
class Card010 final : public Minion
{
public:
    Card010() = default;
    void use(Plate *p,Card *target);
    void atkIncrease(int i);
};
class Card011 final : public Minion
{
public:
    Card011() = default;
    void use(Plate *p,Card *target);
    void atkIncrease(int i);
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
class Card109 final : public Spell
{
public:
    Card109() = default;
    void use(Plate *p,Card *target);
};
class Card110 final : public Spell
{
public:
    Card110() = default;
    void use(Plate *p,Card *target);
};
class Card111 final : public Spell
{
public:
    Card111() = default;
    void use(Plate *p,Card *target);
};
class Card112 final : public Spell
{
public:
    Card112() = default;
    void use(Plate *p,Card *target);
};
class Card113 final : public Spell
{
public:
    Card113() = default;
    void use(Plate *p,Card *target);
};
class Card114 final : public Spell
{
public:
    Card114() = default;
    void use(Plate *p,Card *target);
};
class Card115 final : public Spell
{
public:
    Card115() = default;
    void use(Plate *p,Card *target);
};
class Card116 final : public Spell
{
public:
    Card116() = default;
    void use(Plate *p,Card *target);
};
class Card117 final : public Spell
{
public:
    Card117() = default;
    void use(Plate *p,Card *target);
};
class Card118 final : public Spell
{
public:
    Card118() = default;
    void use(Plate *p,Card *target);
};


/////////////////weapons/////////////////
class Card201 final : public Weapon
{
public:
    Card201() = default;
};
class Card202 final : public Weapon
{
public:
    Card202() = default;
    void usedOnce();
};
#endif // CARDS_H_AMAGOOD

