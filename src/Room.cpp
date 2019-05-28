#include "Room.h"

#include <cmath>
#include <ctime>
#include <limits>
#include <chrono>
#include <thread>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "ACGFunctions.h"

Room::Room(uint32_t id, const std::string& name, const std::string& password, uint32_t playerid) : _ID(id), _name(name), _password(password)
{
    _player.push_back(playerid);
}
Room::~Room()
{
    _player.clear();
    _player.shrink_to_fit();
}
Room* Room::createRoom(uint32_t player, RoomMode mode, uint32_t id, const std::string& name, const std::string& password)
{
    switch(mode)
    {
        case SINGLE_ROOM:
            break;
        case ONEONONE_ROOM:
            return new OneOnOneRoom(id, name, password, player);
        case LADDER_ROOM:
            return new LadderRoom(id, name, password, player);
        default:
            break;
    }
    return nullptr;
}



constexpr short OneOnOneRoom::MaxPlayerNum;
bool OneOnOneRoom::addPlayer(uint32_t playerid)
{
    if(isFull()) return false;
    _player.push_back(playerid);
    return true;
}
void OneOnOneRoom::startGame(std::vector<Deck&> deck)
{
    //deskController = DeskController(deck[0], deck[1]);
    deck.clear();
    deck.shrink_to_fit();
}
void OneOnOneRoom::endGame()
{

}
uint32_t OneOnOneRoom::getWinnerID()
{

}
uint32_t OneOnOneRoom::getLoserID()
{

}


constexpr short OneOnOneRoom::MaxPlayerNum;
bool LadderRoom::addPlayer(uint32_t playerid)
{
    if(isFull()) return false;
    _player.push_back(playerid);
    return true;
}
void LadderRoom::startGame(std::vector<Deck&> deck)
{
    //deskController = DeskController(deck[0], deck[1]);
    deck.clear();
    deck.shrink_to_fit();
}
void LadderRoom::endGame()
{

}
uint32_t LadderRoom::getWinnerID()
{

}
uint32_t LadderRoom::getLoserID()
{

}
int LadderRoom::getWinnerScore()
{
    return 30;
}
int LadderRoom::getLoserScore()
{
    return -5;
}

/*OneOnOneRoom::~OneOnOneRoom()
{
    for(Player* p : _player)
        delete p;
    _player.clear();
    _player.shrink_to_fit();
}*/
/*
bool OneOnOneRoom::addPlayer(Player* player)
{
    if(isFull())
        return false;
    _player.push_back(player);
    return true;
}
void OneOnOneRoom::startGame(Reader *reader, Sender *sender)
{
    Player & p0=*_player[0];
    Player & p1=*_player[1];
    _desk = new Desk(reader, sender, _ID, p0.getDeck(), p1.getDeck(), p0.getName(), p1.getName());
    while(!_endgame)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        _endgame=_desk->isEnd();
    }
}
void OneOnOneRoom::endGame()
{
    delete _desk;
}
uint32_t OneOnOneRoom::getWinnerID()
{
    return _desk->getWinPlayer();
}
uint32_t OneOnOneRoom::getLoserID()
{
    return _player[(int)(_player[0]->getID()==getWinnerID())]->getID();
}
*/



//constexpr short LadderRoom::MaxPlayerNum;
/*LadderRoom::~LadderRoom()
{
    for(Player* p : _player)
        delete p;
    _player.clear();
    _player.shrink_to_fit();
}*/
/*
bool LadderRoom::addPlayer(Player* player)
{
    if(isFull())
        return false;
    _player.push_back(player);
    return true;
}
void LadderRoom::startGame(Reader *reader, Sender *sender)
{
    Player & p0=*_player[0];
    Player & p1=*_player[1];
    _desk = new Desk(reader, sender, _ID, p0.getDeck(), p1.getDeck(), p0.getName(), p1.getName());
    while(!_endgame)
    {
        ACGFunction::sleep(1000);
//        this_thread::sleep_for(std::chrono::seconds(1));
        _endgame=_desk->isEnd();
    }
}
void LadderRoom::endGame()
{
    delete _desk;
}
uint32_t LadderRoom::getWinnerID()
{
    return _desk->getWinPlayer();
}
uint32_t LadderRoom::getLoserID()
{
    return _player[(int)(_player[0]->getID()==getWinnerID())]->getID();
}








Arena_::Arena_(Reader *in, Sender *out, AccountSystem* acc)
{
    srand( time(NULL) );
    initArena();
    reader = in;
    sender = out;
    account = acc;
    std::thread tCheck(&Arena_::checkRooms, this);
    tCheck.detach();
    std::thread tRead(&Arena_::readJson, this);
    tRead.detach();
}
Arena_::~Arena_()
{
    running=false;
    freeAllRooms();
}
bool Arena_::enterRoom(uint32_t playerID, RoomMode mode, int id, std::string password)
{
    Room* room=getRoom(mode, id);
    if(!room->isPasswordCorrect(password))
        return false;
    return room->addPlayer(createPlayer(playerID));
}
void Arena_::enterRoomRandom(uint32_t playerID, RoomMode mode)
{
    Player* player=createPlayer(playerID);
    bool enter=false;
    for(size_t i=0; i<_room[mode].size(); i++)
        if(_room[mode][i]->addPlayer(player))
            enter=true;
    if(!enter)
        createRoom(player, mode, getNonRepeatRandomRoomID(), getNonRepeatRandomRoomName(mode), "");
}
int Arena_::createRoom(uint32_t playerID, RoomMode mode, std::string name, std::string password)
{
    if(!isRoomNameAdmitted(name, mode))
        return -1;
    int id=getNonRepeatRandomRoomID();
    createRoom(createPlayer(playerID), mode, id, name, password);
    return id;
}
bool Arena_::inviteFriend(uint32_t playerID, RoomMode mode, int id)
{
    Room* room=getRoom(mode, id);
    return room->addPlayer(createPlayer(playerID));
}
void Arena_::readJson()
{
    while(true)
    {
        nlohmann::json input;
        input = reader->popJson(jsonType, jsonID);
        RoomMode mode=(RoomMode)input["data"]["roomMode"];
        switch((ActionType)getActionType(input["data"]["action"]))
        {
            case GET_ROOMLIST:
                returnRoomList(mode);
                break;
            case GET_ROOMINFO:
                returnRoomInfo(mode, input["data"]["roomId"]);
                break;
            case CREATE_ROOM:
                returnCreateRoom((uint32_t)input["data"]["userId"], mode, input["data"]["roomName"], input["data"]["roomPassword"]);
                break;
            case ENTER_ROOM:
                returnEnterRoom((uint32_t)input["data"]["userId"], mode, input["data"]["roomId"], input["data"]["roomPassword"]);
                break;
            case ENTER_ROOM_RANDOM:
                enterRoomRandom((uint32_t)input["data"]["userId"], mode);
                break;
            case INVITE_FRIEND:
                inviteFriend((uint32_t)input["data"]["userId"], mode, input["data"]["roomId"]);
                break;
            default:
                break;
        }
    }
}
///private
void Arena_::initArena()
{
    for(int i=0; i<ROOMMODE_COUNT; i++)
        _room[i].clear();
    actionString[0] = "getRoomList";
    actionString[1] = "getRoomInfo";
    actionString[2] = "createRoom";
    actionString[3] = "enterRoom";
    actionString[4] = "enterRoomRandom";
    actionString[5] = "inviteFriend";
}
int Arena_::getNonRepeatRandomRoomID()
{
    int num=(rand()%std::numeric_limits<int>::max())/10;
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
                    num=rand()%std::numeric_limits<int>::max();
                    newnum=true;
                    break;
                }
            }
        }
    }
    return num;
}
std::string Arena_::getRandomString(RoomMode mode)
{
    static const std::string alphanum =
            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int len=4;
    while(_room[mode].size()>pow(sizeof(alphanum)/2, len)/2)
        len++;
    std::string str;
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
bool Arena_::isRoomNameAdmitted(std::string name, RoomMode mode)
{
    for(size_t i=0; i<_room[mode].size(); i++)
        if(name==_room[mode][i]->getName())
            return false;
    return true;
}
std::string Arena_::getNonRepeatRandomRoomName(RoomMode mode)
{
    std::string str=getRandomString(mode);
    while(!isRoomNameAdmitted(str, mode))
        str=getRandomString(mode);
    return str;
}
Room* Arena_::getRoom(RoomMode mode, int id)
{
    for(size_t i=0; i<_room[mode].size(); i++)
        if(_room[mode][i]->getID()==id)
            return _room[mode][i];
    return nullptr;
}
void Arena_::createRoom(Player* player, RoomMode mode, int id, std::string name, std::string password)
{
    Room* room = Room::createRoom(player, mode, id, name, password);
    _room[mode].push_back(room);
}
void Arena_::freeAllRooms()
{
    for(int i=0; i<ROOMMODE_COUNT; i++)
    {
        _room[i].clear();
        _room[i].shrink_to_fit();
        //vector<Room*>().swap(_room[i]);
    }
}
Player* Arena_::createPlayer(uint32_t playerID)
{
    std::string playerName = account->getAccountName(playerID);
    U32vec playerDeck = account->getDeck(playerID);
    return new Player(playerID, playerName, playerDeck);
}
void Arena_::checkRooms()
{
    while(running)
    {
        ACGFunction::sleep(1000);
        for(int mode=0; mode<ROOMMODE_COUNT; mode++)
        {
            for(size_t i=0; i<_room[mode].size(); i++)
            {
                if(_room[mode][i]->isGameEnd())
                {
                    // FIXME
                    //account->update(_room[mode][i]->getWinnerID(), _room[mode][i]->getLoserID(), (int)mode);
                    _room[mode][i]->endGame();
                    delete _room[mode][i];
                    _room[mode][i] = nullptr;
                    _room[mode].erase(std::remove(_room[mode].begin(), _room[mode].end(), nullptr), _room[mode].end());
                }
            }
        }
    }
}

void Arena_::start(Room* room, Reader* reader, Sender* sender)
{
    room->startGame(reader, sender);
}

void Arena_::startGame(RoomMode mode, int id)
{
    Room* room = getRoom(mode, id);
    std::thread tGame(&Arena::start, this, room, reader, sender);
    tGame.detach();
}


void Arena_::setJson(json & j)
{
    j["time"]=time(NULL);
    j["type"]=jsonType;
    j["userId"]=jsonID;
    j["deviceId"]="";
    j["data"]["eventType"]=jsonType;
}
int Arena_::getActionType(std::string action)
{
    for(int i=0;i<(int)ActionType::ACTION_COUNT;i++)
        if(action==actionString[i])
            return i;
    return (int)ActionType::ACTION_COUNT;
}
void Arena_::returnRoomList(RoomMode mode)
{
    std::vector<int> roomID;
    for(size_t i=0; i<_room[mode].size(); i++)
        roomID.push_back(_room[mode][i]->getID());
    json j;
    setJson(j);
    j["data"]["action"]="getRoomList";
    j["data"]["roomMode"]=(int)mode;
    j["data"]["roomId"]=roomID;
    std::cout << j <<std::endl;
}
void Arena_::returnRoomInfo(RoomMode mode, int roomId)
{
    Room* room = getRoom(mode, roomId);
    std::vector<uint32_t> playerID;
    for(size_t i=0; i<room->getPlayers().size(); i++)
        playerID.push_back(room->getPlayers()[i]->getID());
    json j;
    setJson(j);
    j["data"]["action"]="getRoomInfo";
    j["data"]["roomMode"]=(int)mode;
    j["data"]["roomId"]=roomId;
    j["data"]["roomName"]=room->getName();
    j["data"]["playerId"]=playerID;
    std::cout << j << std::endl;
}
void Arena_::returnCreateRoom(uint32_t playerID, RoomMode mode, std::string name, std::string password)
{
    int roomId = createRoom(playerID, mode, name, password);
    json j;
    setJson(j);
    j["data"]["roomMode"]=(int)mode;
    j["data"]["action"]="createRoom";
    j["data"]["userId"]=playerID;
    if(roomId>=0)
    {
        Room* room = getRoom(mode, roomId);
        j["data"]["result"]=1;
        j["data"]["roomId"]=room->getID();
        j["data"]["roomName"]=room->getName();
    }
    else
    {
        j["data"]["result"]=0;
        j["data"]["roomId"]=-1;
        j["data"]["roomName"]="";
    }
}
void Arena_::returnEnterRoom(uint32_t playerID, RoomMode mode, int id, std::string password)
{
    bool enter = enterRoom(playerID, mode, id, password);
    json j;
    setJson(j);
    j["data"]["roomMode"]=(int)mode;
    j["data"]["action"]="enterRoom";
    j["data"]["roomId"]=id;
    j["data"]["userId"]=playerID;
    j["data"]["result"]=(int)enter;
}
*/