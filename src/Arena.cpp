#include <iostream>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "Router.h"
#include "Room.h"
#include "Arena.h"


Arena::Arena()
{
    _initArena();
}
Arena::~Arena()
{
    _running=false;
    _delAllRooms();
}

int Arena::createRoom(uint32_t playerID, RoomMode mode, const std::string& name, const std::string& password)
{
    if(!_isRoomNameAdmitted(name, mode))
        return -1;
    uint32_t id=_getNonRepeatRandomRoomID();
    _createRoom(playerID, mode, _getNonRepeatRandomRoomID(), name, password);
    return id;
}
bool Arena::enterRoom(uint32_t playerID, RoomMode mode, uint32_t id, const std::string& password)
{
    Room* room=_getRoom(mode, id);
    if(!room->isPasswordCorrect(password))
        return false;
    return room->addPlayer(playerID);
}
void Arena::enterRoomRandom(uint32_t playerID, RoomMode mode)
{
    bool enter=false;
    for(size_t i=0; i<_room[mode].size(); i++)
        if(_room[mode][i]->addPlayer(playerID))
            enter=true;
    if(!enter)
        _createRoom(playerID, mode, _getNonRepeatRandomRoomID(), _getNonRepeatRandomRoomName(mode));
}
bool Arena::inviteFriend(uint32_t playerID, RoomMode mode, uint32_t id)
{
    Room* room=_getRoom(mode, id);
    return room->addPlayer(playerID);
}




void Arena::_initArena()
{
    for(int mode=0; mode<ROOMMODE_COUNT; mode++)
        _room[mode].clear();
}
void Arena::_delAllRooms()
{
    for(int mode=0; mode<ROOMMODE_COUNT; mode++)
    {
        for(auto r : _room[mode])
            delete r;
        _room[mode].clear();
        _room[mode].shrink_to_fit();
    }
}
bool Arena::_isRoomNameAdmitted(const std::string& name, RoomMode mode)
{
    for(size_t i=0; i<_room[mode].size(); i++)
        if(name==_room[mode][i]->getName())
            return false;
    return true;
}
uint32_t Arena::_getNonRepeatRandomRoomID()
{
    uint32_t num=rand()%10+1;
    bool newnum=true;
    while(newnum)
    {
        newnum=false;
        for(int mode=0; mode<ROOMMODE_COUNT; mode++)
        {
            for(size_t i=0; i<_room[mode].size(); i++)
            {
                if(num==_room[mode][i]->getID())
                {
                    num+=rand()%10+1;
                    newnum=true;
                    break;
                }
            }
            if(newnum) break;
        }
    }
    return num;
}
void Arena::_createRoom(uint32_t player, RoomMode mode, uint32_t id, const std::string& name, const std::string& password)
{
    Room* room = Room::createRoom(player, mode, id, name, password);
    _room[mode].push_back(room);
}
Room* Arena::_getRoom(RoomMode mode, uint32_t id)
{
    for(size_t i=0; i<_room[mode].size(); i++)
        if(_room[mode][i]->getID()==id)
            return _room[mode][i];
    return nullptr;
}
std::string Arena::_getNonRepeatRandomRoomName(RoomMode mode)
{
    std::string str=_getRandomString(mode);
    while(!_isRoomNameAdmitted(str, mode))
        str=_getRandomString(mode);
    return str;
}
std::string Arena::_getRandomString(RoomMode mode)
{
    static const std::string alphanum =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int len=4;
    while(_room[mode].size()>pow(alphanum.size()/2, len)/2)
        len++;
    std::string str="";
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
        str += alphanum[rand() % (alphanum.size() - 1)];
    str[len] = 0;
    return str;
}

void Arena::startGame(RoomMode mode, uint32_t id)
{
    Room* room = _getRoom(mode, id);
    std::vector<Deck&> deck;
    //for(uint32_t player : room->getPlayers())
    //    deck.push_back(_account->getAccountDeck(player));
    room->startGame(deck);
}

