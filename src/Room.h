#include "Desk.h"
#include "Deck.h"
#include <vector>
#include <string>
#include <iostream>
#include "AccountSystem.h"
#include "nlohmann/json.hpp"
#include "Reader.h"
#include "Printer.h"


#ifndef PLAYER
#define PLAYER
class Player
{
public:
    Player(uint32_t id, std::string name, Deck & deck) : _ID(id), _name(name), _deck(deck){}
    uint32_t getID() const { return _ID; }
    std::string getName() const { return _name; }
    Deck & getDeck() const { return _deck; }
private:
    uint32_t _ID;
    std::string _name;
    Deck & _deck;
};
#endif // PLAYER

#ifndef ROOM
#define ROOM
enum RoomMode { SINGLE_ROOM=0, ONEONONE_ROOM, LADDER_ROOM, ROOMMODE_COUNT};
class Room
{
public:
    Room(int id, std::string name, std::string word, Player* player);
    ~Room();
    static Room* createRoom(Player* player, RoomMode mode, int id, std::string name, std::string password);
    int getID() const { return _ID; }
    std::string getName() const { return _name; }
    std::vector<Player*> getPlayers() const { return _player; }
    RoomMode getRoomMode() const { return _mode; }
    bool isPasswordCorrect(std::string word) const { return _password=="" || _password==word; }
    bool isGameEnd() const { return _endgame; }
    virtual bool isFull() const =0;
    virtual bool addPlayer(Player* player)=0;
	virtual void startGame()=0;
	virtual void endGame()=0;
	virtual bool invitePlayer(int id)=0;
    virtual uint32_t getWinnerID()=0;
    virtual uint32_t getLoserID()=0;
protected:
    int _ID;
    std::string _name;
    std::string _password;
    std::vector<Player*> _player;
    RoomMode _mode;
    bool _endgame=false;
};
class OneOnOneRoom : public Room
{
public:
    OneOnOneRoom(int id, std::string name, std::string word, Player* player) : Room(id, name, word, player) { _mode = ONEONONE_ROOM; }
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(Player* player) override;
    bool invitePlayer(int id) override;
	void startGame() override;
	void endGame() override;
	uint32_t getWinnerID() override;
	uint32_t getLoserID() override;
private:
    Desk* _desk;
    static constexpr short MaxPlayerNum=2;
};
class LadderRoom : public Room
{
public:
    LadderRoom(int id, std::string name, std::string word, Player* player) : Room(id, name, word, player) { _mode = LADDER_ROOM; }
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(Player* player) override;
    bool invitePlayer(int id) override;
	void startGame() override;
	void endGame() override;
	uint32_t getWinnerID() override;
	uint32_t getLoserID() override;
private:
    static constexpr short MaxPlayerNum=2;
};
#endif // ROOM

#ifndef ARENA
#define ARENA
class Arena
{
    friend std::ostream & operator << (std::ostream & os, const Arena* arena);
public:
    Arena(Reader *in, Sender *out, AccountSystem *acc);
    ~Arena();
    ///建立房間，建立成功回傳id，-1:Failed，名稱重複
    int createRoom(uint32_t playerID, RoomMode mode, std::string name, std::string password);
    bool enterRoom(uint32_t playerID, RoomMode mode, int id, std::string password);
    void enterRoomRandom(uint32_t playerID, RoomMode mode);
    void inviteFriend(uint32_t playerID, RoomMode mode, int id);
    void readJson();
private:
    Reader *reader;
    Sender *sender;
    AccountSystem* account;
    std::vector<Room*> _room[ROOMMODE_COUNT];
    bool running=true;
    const std::string jsonType="room";
    const int jsonID=123;
    void initArena();
    int getNonRepeatRandomRoomID(RoomMode mode);
    std::string getRandomString(RoomMode mode);
    std::string getNonRepeatRandomRoomName(RoomMode mode);
    void createRoom(Player* player, RoomMode mode, int id, std::string name, std::string password);
    Room* getRoom(RoomMode mode, int id);
    bool isRoomNameAdmitted(std::string name, RoomMode mode);
    Player* createPlayer(uint32_t playerID);
    void checkRooms();
    void startGame(RoomMode mode, int id);
    void freeAllRooms();
    ///UI
    enum ActionType { GET_ROOMLIST=0, GET_ROOMINFO, CREATE_ROOM, ENTER_ROOM, ENTER_ROOM_RANDOM, INVITE_FRIEND, ACTION_COUNT};
    static const std::string actionString[];
    void setJson(json& j);
    int getActionType(std::string action);
    void returnRoomList(RoomMode mode);
    void returnRoomInfo(RoomMode mode, int roomId);
    void returnCreateRoom(uint32_t playerID, RoomMode mode, std::string name, std::string password);
    void returnEnterRoom(uint32_t playerID, RoomMode mode, int id, std::string password);
};
const std::string Arena::actionString[]={"getRoomList", "getRoomInfo", "createRoom", "enterRoom", "enterRoomRandom", "inviteFriend"}
#endif // ARENA

