#include "Room.h"
#include <math.h>
#include <time.h>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include "Account.h"
#include "Timer.h"

using namespace std;

Room::Room(int id, string name, string word, Player* player) : _ID(id), _name(name), _password(word)
{
    _player.push_back(player);
}
Room::~Room()
{
    _player.clear();
    _player.shrink_to_fit();
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
    //Desk* desk;
    //desk = new Desk(p0.getDeck(), p1.getDeck(), p0.getName(), p1.getName());
    //int winner = desk->getWinPlayer();
    //delete desk;
}
bool OneOnOneRoom::invitePlayer(int id)
{
    if(isFull())
        return false;
    Player* player=new Player(id, Account::getPlayerName(id), Account::getPlayerDeck(id));
    return addPlayer(player);
}
void OneOnOneRoom::sendGameResult()
{

}


constexpr short LadderRoom::MaxPlayerNum;
bool LadderRoom::addPlayer(Player* player)
{
    if(isFull())
        return false;
    _player.push_back(player);
    return true;
}
void LadderRoom::startGame()
{
    Player & p0=*_player[0];
    Player & p1=*_player[1];
    //Desk* desk = new Desk(p0.getDeck(), p1.getDeck(), p0.getName(), p1.getName());
    //int winner = desk->getWinPlayer();
    //delete desk;
}
bool LadderRoom::invitePlayer(int id)
{
    if(isFull())
        return false;
    Player* player=new Player(id, Account::getPlayerName(id), Account::getPlayerDeck(id));
    return addPlayer(player);
}
void LadderRoom::sendGameResult()
{

}


Arena::Arena()
{
    srand( time(NULL) );
    initArena();
}
Arena::~Arena()
{
    freeAllRooms();
}
bool Arena::enterRoom(int playerID, std::string playerName, Deck & playerDeck, RoomMode mode, int id, string password)
{
    Room* room=getRoom(mode, id);
    if(!room->isPasswordCorrect(password))
        return false;
    Player* player=new Player(playerID, playerName, playerDeck);
    return room->addPlayer(player);
}
void Arena::enterRoomRandom(int playerID, std::string playerName, Deck & playerDeck, RoomMode mode)
{
    Player* player=new Player(playerID, playerName, playerDeck);
    bool enter=false;
    for(size_t i=0; i<_room[mode].size(); i++)
        if(_room[mode][i]->addPlayer(player))
            enter=true;
    if(!enter)
        createRoom(player, mode, getNonRepeatRandomRoomID(mode), getNonRepeatRandomRoomName(mode), "");
}
bool Arena::createRoom(int playerID, std::string playerName, Deck & playerDeck, RoomMode mode, string name, string password)
{
    if(!isRoomNameAdmitted(name, mode))
        return false;
    Player* player=new Player(playerID, playerName, playerDeck);
    createRoom(player, mode, getNonRepeatRandomRoomID(mode), name, password);
    return true;
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
    case LADDER_ROOM:
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
bool Arena::isRoomNameAdmitted(string name, RoomMode mode)
{
    for(size_t i=0; i<_room[mode].size(); i++)
        if(name==_room[mode][i]->getName())
            return false;
    return true;
}
string Arena::getNonRepeatRandomRoomName(RoomMode mode)
{
    string str=getRandomString(mode);
    while(!isRoomNameAdmitted(str, mode))
        str=getRandomString(mode);
    return str;
}
Room* Arena::getRoom(RoomMode mode, int id)
{
    for(size_t i=0; i<_room[mode].size(); i++)
        if(_room[mode][i]->getID()==id)
            return _room[mode][i];
    return nullptr;
}
void Arena::createRoom(Player* player, RoomMode mode, int id, string name, string password)
{
    switch(mode)
    {
    case SINGLE_ROOM:
        break;
    case ONEONONE_ROOM:
        _room[mode].push_back(new OneOnOneRoom(id, name, password, player));
        break;
    case LADDER_ROOM:
        _room[mode].push_back(new LadderRoom(id, name, password, player));
        break;
    default:
        break;
    }
}
void Arena::freeAllRooms()
{
    for(int i=0; i<ROOMMODE_COUNT; i++)
    {
        _room[i].clear();
        _room[i].shrink_to_fit();
        //vector<Room*>().swap(_room[i]);
    }
}
