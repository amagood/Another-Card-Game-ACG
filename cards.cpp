#include "cards.h"
Card::Card(int attack,int healthPoint,int mannaRequired)
{
    atk=attack;
    hp=healthPoint;
    mp=mannaRequired;
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
