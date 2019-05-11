#include "cards.h"

constexpr maxHp = 30;
Card::Card(int attack,int healthPoint,int mannaRequired,int ID, std::string Name)
{
    atk=attack;
    hp=healthPoint;
    mp=mannaRequired;
	ID=id;
	name=Name
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
    hp--;
}


void Minion::attack(Minion &target)
{
    hp-=target.atk;
    target.hp-=atk;

    ///both hasn't checked <die>
}

////////////////////////Cards ///////////////
Hero::Hero()
{
	id = 0;
	atk = 0;
	hp = maxHp
	mp = 0;
	
}

Card001::Card001()
{
	id=1;
	atk = 1;
	hp = 2;
	mp = 1;
	name = "戰士學徒";
}