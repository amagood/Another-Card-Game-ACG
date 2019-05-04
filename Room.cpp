#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <math.h>
#include <time.h>
#include "Room.h"

using namespace std;

Room::Room(int id, string name, string word, Player* player) : _ID(id), _name(name), _password(word)
{
    _player.push_back(player);
}
constexpr short OneOnOneRoom::MaxPlayerNum;
bool OneOnOneRoom::addPlayer(Player* player)
{
    if(isFull())
        return false;
    _player.push_back(player);
    return true;
}
void OneOnOneRoom::startGame()
{
    Player & p0=*_player[0];
    Player & p1=*_player[1];
    Desk* desk = new Desk(p0.getDeck(), p1.getDeck(), p0.getName(), p1.getName());
    //int winner = desk->getWinPlayer();
    delete desk;
}

Arena::Arena()
{
    srand( time(NULL) );
    initArena();
}
Arena::~Arena()
{
    freeRoom();
}
void Arena::enterRoom(int playerID, std::string playerName, Deck playerDeck, RoomMode mode)
{
    Player* player=new Player(playerID, playerName, playerDeck);
    bool enter=false;
    for(size_t i=0; i<_room[mode].size(); i++)
        if(_room[mode][i]->addPlayer(player))
            enter=true;
    if(!enter)
        createRoom(player, mode, getNonRepeatRandomRoomID(mode), getNonRepeatRandomRoomName(mode), "");
}
void Arena::createRoom(int playerID, std::string playerName, Deck playerDeck, RoomMode mode, string name, string password)
{
    Player* player=new Player(playerID, playerName, playerDeck);
    createRoom(player, mode, getNonRepeatRandomRoomID(mode), name, password);
}
void Arena::initArena()
{
    for(int i=0; i<ROOMMODE_COUNT; i++)
        _room[i].clear();
}
int Arena::getNonRepeatRandomRoomID(RoomMode mode)
{
    int num=(rand()%numeric_limits<int>::max())/10;
    bool newnum=true;
    while(newnum)
    {
        newnum=false;
        for(size_t i=0; i<_room[mode].size(); i++)
        {
            if(num==_room[mode][i]->getID())
            {
                num=rand()%numeric_limits<int>::max();
                newnum=true;
                break;
            }
        }
    }
    return num;
}
string Arena::getRandomString(RoomMode mode)
{
    static const string alphanum ="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int len=4;
    while(_room[mode].size()>pow(sizeof(alphanum)/2, len)/2)
        len++;
    string str;
    switch(mode)
    {
    case SINGLE_ROOM:
        str[0]='S';
        break;
    case ONEONONE_ROOM:
        str[0]='O';
        break;
    case RANKING_ROOM:
        str[0]='R';
        break;
    default:
        break;
    }
    for (int i = 0; i < len; ++i)
        str += alphanum[rand() % (sizeof(alphanum) - 1)];
    str[len] = 0;
    return str;
}
string Arena::getNonRepeatRandomRoomName(RoomMode mode)
{
    string str=getRandomString(mode);
    bool newstr=true;
    while(newstr)
    {
        newstr=false;
        for(size_t i=0; i<_room[mode].size(); i++)
        {
            if(str==_room[mode][i]->getName())
            {
                str=getRandomString(mode);
                newstr=true;
                break;
            }
        }
    }
    return str;
}
void Arena::createRoom(Player* player, RoomMode mode, int id, string name, string password)
{
    _room[mode].push_back(new OneOnOneRoom(id, name, password, player));
}
void Arena::freeRoom()
{
    for(int i=0; i<ROOMMODE_COUNT; i++)
    {
        _room[i].clear();
        _room[i].shrink_to_fit();
        //vector<Room*>().swap(_room[i]);
    }
}
