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
    //std::vector<Card *> deck=p->hand[playerId];
    p->hand[playerId].at(0)->atkIncrease(atk);
}
void Weapon::usedOnce()
{
    hpIncrease(-1);
}
Weapon :: ~Weapon()
{
    int playerId=holdPlate->whosTurn?1:0 ;
    //std::vector<Card *> deck=holdPlate->hand[playerId];
    holdPlate->hand[playerId].at(0)->setAtk(0);

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
    //std::vector<Card *> deck=p->hand[targetPlayer];
    atkIncrease(p->GodHpAtk);
    hpIncrease(p->GodHpAtk);

    for(int i=0;i<atk;i++)
    {
        p->hand[targetPlayer].at(rand()%p->hand[targetPlayer].size())->hpIncrease(-1);
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
void Card005::use(Plate *p,Card *card)
{
    p->GodHpAtk+=1;
    int usePlayer = (p->whosTurn?1:0);
    draw(p->hand[usePlayer],p->playerDeck[usePlayer]);  //draw 1 card out
}
void Card006::use(Plate *p,Card *card)
{
    p->GodHpAtk+=1;
    int usePlayer = (p->whosTurn?1:0);
    draw(p->hand[usePlayer],p->playerDeck[usePlayer]);  //draw 1 card out

    card->hpIncrease(-2);
}
void Card007::use(Plate *p,Card *card)
{
    holdPlate=p;
}
void Card007::attack(Minion &target)
{
    hpIncrease(-target.getAtk());
    target.hpIncrease(-getAtk());

    holdPlate->GodHpAtk+=1;
}
void Card008::use(Plate *p,Card *card)
{
    holdPlate=p;
}
void Card008::attack(Minion &target)
{
    hpIncrease(-target.getAtk());
    target.hpIncrease(-getAtk());

    int usePlayer = (holdPlate->whosTurn?1:0);
    draw(holdPlate->hand[usePlayer],holdPlate->playerDeck[usePlayer]);  //draw 1 card out
}

void Card009::use(Plate *p,Card *card)
{
    Minion *tmp=(Minion *)card;
    this->attack(*tmp);
}
void Card010::use(Plate *p,Card *card)
{
    holdPlate=p;
}
void Card010::atkIncrease(int i)
{
    if(i<0)
    {
        int usePlayer = (holdPlate->whosTurn?1:0);
        draw(holdPlate->hand[usePlayer],holdPlate->playerDeck[usePlayer]);  //draw 1 card out
    }
}
void Card011::use(Plate *p,Card *card)
{
    holdPlate=p;
}
void Card011::atkIncrease(int i)
{
    if(i<0)
    {
        int usePlayer = (holdPlate->whosTurn?1:0);
        for(auto i:holdPlate->BF[(usePlayer+1)%2])
        {
            i->hpIncrease(-5);
        }
    }
}

void Card012::use(Plate *p,Card *card)
{
    holdPlate=p;
}
void Card012::attack(Minion &target)
{
    hpIncrease(-target.getAtk());
    target.hpIncrease(-getAtk());

    int usePlayer = (holdPlate->whosTurn?1:0);
    for(auto i:holdPlate->BF[(usePlayer+1)%2])
    {
        i->hpIncrease(-getAtk());
    }
}

void Card013::use(Plate *p,Card *card)
{
    int usePlayer = (p->whosTurn?1:0);
    p->BF[usePlayer].emplace_back(new Card013);
}
void Card014::attack(Minion &target)
{
    bool critical = (rand()%2);

    hpIncrease(-target.getAtk());
    if(critical)
        target.hpIncrease(-getAtk()*2);
    else
        target.hpIncrease(-getAtk());

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
void Card103::use(Plate *p,Card *target)
{
    int usePlayer = (p->whosTurn?1:0);
    for (int i=0;i<3;i++) {
        draw(p->hand[usePlayer],p->playerDeck[usePlayer]);  //draw 1 card out
    }
}
void Card104::use(Plate *p,Card *target)
{
    int usePlayer = (p->whosTurn?1:0);
    for (int i=0;i<5;i++) {
        draw(p->hand[usePlayer],p->playerDeck[usePlayer]);  //draw 1 card out
    }
    target->hpIncrease(-3);
}
void Card105::use(Plate *p,Card *target)
{
    target->hpIncrease(-2);
}
void Card106::use(Plate *p,Card *target)
{
    target->hpIncrease(-6);
}
void Card107::use(Plate *p,Card *target)
{
    target->hpIncrease(-8);
}
void Card108::use(Plate *p,Card *target)
{
    int usePlayer = (p->whosTurn?1:0);
    draw(p->hand[usePlayer],p->playerDeck[usePlayer]);  //draw 1 card out
    target->hpIncrease(-10);
}
void Card109::use(Plate *p,Card *target)
{
    int usePlayer = (p->whosTurn?1:0);
    target->hpIncrease(-5);
    for(auto i:p->BF[(usePlayer+1)%2])
    {
        i->hpIncrease(-5);
    }
}
void Card110::use(Plate *p,Card *target)
{
    target->hpIncrease(2);
}
void Card111::use(Plate *p,Card *target)
{
    target->hpIncrease(5);
}
void Card112::use(Plate *p,Card *target)
{
    target->hpIncrease(8);
}
void Card113::use(Plate *p,Card *target)
{
    int usePlayer = (p->whosTurn?1:0);
    for(auto i:p->BF[(usePlayer+1)%2])
    {
        i->hpIncrease(8);
    }
}
void Card114::use(Plate *p,Card *target)
{
    target->hpIncrease(2);
    target->atkIncrease(2);
}
void Card115::use(Plate *p,Card *target)
{
    target->hpIncrease(4);
    target->atkIncrease(5);
}
void Card116::use(Plate *p,Card *target)
{
    target->hpIncrease(4);
    target->atkIncrease(8);
}
void Card117::use(Plate *p,Card *target)
{
    int usePlayer = (p->whosTurn?1:0);
    for(auto i:p->BF[(usePlayer+1)%2])
    {
        i->hpIncrease(5);
        i->atkIncrease(5);
    }
}
void Card118::use(Plate *p,Card *target)
{
    int usePlayer = (p->whosTurn?1:0);
    if(target->getId()!=0)    //if target isn't hero
    {
        target->hpIncrease(12);
        target->atkIncrease(12);

        //auto hero=p->BF[p->whosTurn].at(0);
        p->BF[p->whosTurn].at(0)->hpIncrease((p->BF[p->whosTurn].at(0)->getHp())/2);
    }
}
//////////////////////////////weapons///////////////////
void Card202::usedOnce()
{
    hpIncrease(-1);
    atkIncrease(-1);
    int playerId=holdPlate->whosTurn?1:0 ;
    //std::vector<Card *> deck=holdPlate->hand[playerId];
    holdPlate->hand[playerId].at(0)->atkIncrease(-1);   //hero atk-=1
}
void Card203::usedOnce()
{
    hpIncrease(-1);
    atkIncrease(-1);
    int playerId=holdPlate->whosTurn?1:0 ;
    //std::vector<Card *> deck=holdPlate->hand[playerId];
    holdPlate->BF[playerId].emplace_back(new Card001);
}