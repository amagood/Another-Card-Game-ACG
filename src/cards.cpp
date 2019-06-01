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
Weapon::use(Plate *p,Card *target)
{

    int playerId=p->whosTurn?1:0 ;

    std::vector<Card *> deck=p->hand.at(playerId).getDeck();
    deck->at(0).atkIncrease(atk);
}
void Weapon::usedOnce()
{
    hpIncrease(-1);
}
Weapon :: ~Weapon()
{
    int playerId=holdDesk->getPlayerId();
    std::vector<Card *> deck=holdDesk->getPlayerDeck().at(playerId).getDeck();
    deck->at(0).atkIncrease(atk*(-1));
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
Card002::Card002()
{
    setId(2);
    setAtk(6);
    setHp(6);
    setMp(10);
    setName("神");
    setAttributes("對隨機目標造成一點傷害，次數等同於攻擊力");
}
Card002::use(Plate *p, Card *card)
{
    int targetPlayer = (1+(p->whosTurn?1:0))%2;
    std::vector<Card *> deck=p->hand.at(targetPlayer).getDeck();
    atkIncrease(p->getGodHpAtk);
    hpIncrease(p->getGodHpAtk);

    for(int i=0;i<atk;i++)
    {
        deck->at(rand()%deck.size()).hpIncrease(-1).
    }
}
Card003::Card003()
{
    setId(3);
    setAtk(2);
    setHp(3);
    setMp(2);
    setName("招邪者");
    setAttributes("你的【神】獲得+1/+1  只要他不在場上");
}
Card003::use(Plate *p,Card *card)
{
    p->setGodHpAtk+=1;
}



//////////////////////////////weapons///////////////////
Card201 :: Card201()
{
    setId(201);
    setAtk(1);
    setHp(2);
    setMp(1);
    setName("小木棒");
}