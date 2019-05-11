#include "cards.h"

constexpr int maxHp = 30;
Card::Card(int attack,int healthPoint,int mannaRequired,int ID, std::string Name)
{
    atk=attack;
    hp=healthPoint;
    mp=mannaRequired;
	ID=id;
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
void Card::setAttributes(string s)
{
	attrib=s;
}
void setId(int num)
{
	id=num;
}
void setName(std::string s)
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
string Card::getAttributes()
{
	return attrib;
}
string Card::getName()
{
	return name;
}


void Weapon::usedOnce()
{
    hpIncrease(-1);
}


void Minion::attack(Minion &target)
{
	hpIncrease(-target.atk);
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