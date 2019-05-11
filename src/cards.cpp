#include "cards.h"

constexpr int maxHp = 30;
Card::Card(int attack,int healthPoint,int mannaRequired,int ID, std::string Name)
{
    atk=attack;
    hp=healthPoint;
    mp=mannaRequired;
	id=ID;
	name=Name;
}
void Card::setAtk(int attack)
{
    atk=attack;
}
void Card::setHp(int healthPoint)
{
    hp=healthPoint;
}
void Card::setMp(int mannaRequired)
{
    mp=mannaRequired;
}
void Card::setAttributes(std::string s)
{
	attrib=s;
}
void Card::setId(int num)
{
	id=num;
}
void Card::setName(std::string s)
{
	name=s;
}


void Card::atkIncrease(int i)
{
    atk+=i;
}
void Card::hpIncrease(int i)
{
    hp+=i;
}

int Card::getAtk()
{
    return atk;
}
int Card::getHp()
{
    return hp;
}
int Card::getMp()
{
    return mp;
}
int Card::getId()
{
	return id;
}
std::string Card::getAttributes()
{
	return attrib;
}
std::string Card::getName()
{
	return name;
}

Weapon::Weapon()
{
	
}

void Weapon::usedOnce()
{
    hpIncrease(-1);
}
Spell::Spell()
{
	
}
Minion::Minion()
{
	
}
void Minion::attack(Minion &target)
{
	hpIncrease(-target.getAtk());
    target.hpIncrease(-getAtk());

    ///both hasn't checked <die>
}

////////////////////////Cards ///////////////

Hero::Hero()
{
	setId(0);
	setAtk(0);
	setHp(maxHp);
	setMp(0);
	setName("英雄");
}

Card001::Card001()
{
	setId(1);
	setAtk(1);
	setHp(2);
	setMp(1);
	setName("戰士學徒");
}