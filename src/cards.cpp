#include <cstdlib>
#include <ctime>
#include "cards.h"
#include <plate.h>
#include "CardInfoSystem.h"
#include <vector>

constexpr int maxHp = 30;

/*
 *
struct Plate
{
    std::vector<Card *> BF[2],hand[2]; //battlefield
    Deck playerDeck[2];
    int playerHp[2];
    int whosTurn;
    int GodHpAtk;
};
 */
void draw(std::vector<Card*> &to,Deck &from)
{
    Card* tmp=from.popDeck(-1);

    to.emplace_back(tmp);

}

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

void Card004::use(Plate *p,Card *card)
{
    p->GodHpAtk+=1;
}
/////////////////spells/////////////////

void Card101::use(Plate *p,Card *target)
{
    int usePlayer = (p->whosTurn?1:0);
    draw(p->hand[usePlayer],p->playerDeck[usePlayer]);  //draw 1 card out

}
void Card102::use(Plate *p,Card *target)
{
    int usePlayer = (p->whosTurn?1:0);
    for (int i=0;i<2;i++) {
        draw(p->hand[usePlayer],p->playerDeck[usePlayer]);  //draw 1 card out
    }
}

//////////////////////////////weapons///////////////////