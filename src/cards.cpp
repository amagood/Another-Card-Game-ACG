#include <cstdlib>
#include <ctime>
#include "cards.h"
#include <plate.h>
#include "CardInfoSystem.h"
#include <Deck.h>
#include <vector>

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
void Weapon::use(Plate *p,Card *target)
{

    int playerId=p->whosTurn?1:0 ;
    holdPlate=p;
    std::vector<Card *> deck=p->hand[playerId];
    deck.at(0)->atkIncrease(atk);
}
void Weapon::usedOnce()
{
    hpIncrease(-1);
}
Weapon :: ~Weapon()
{
    int playerId=holdPlate->whosTurn?1:0 ;
    std::vector<Card *> deck=holdPlate->hand[playerId];
    deck.at(0)->setAtk(0);

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

////////////////////////minions//////////////////

void Card002::use(Plate *p, Card *card)
{
    int targetPlayer = (1+(p->whosTurn?1:0))%2;
    std::vector<Card *> deck=p->hand[targetPlayer];
    atkIncrease(p->GodHpAtk);
    hpIncrease(p->GodHpAtk);

    for(int i=0;i<atk;i++)
    {
        deck.at(rand()%deck.size())->hpIncrease(-1);
    }
}

void Card003::use(Plate *p,Card *card)
{
    p->GodHpAtk+=1;
}



//////////////////////////////weapons///////////////////