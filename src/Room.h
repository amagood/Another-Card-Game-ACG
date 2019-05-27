#ifndef ANOTHER_CARD_GAME_ACG_ROOM_H
#define ANOTHER_CARD_GAME_ACG_ROOM_H

#include <iostream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>

#include "Deck.h"
#include "AccountSystem.h"
#include "DeskController.h"

enum RoomMode { SINGLE_ROOM=0, ONEONONE_ROOM, LADDER_ROOM, ROOMMODE_COUNT};
class Room
{
public:
    Room(uint32_t id, const std::string& name, const std::string& password, uint32_t playerid);
    ~Room();//TODO
    static Room* createRoom(uint32_t player, RoomMode mode, uint32_t id, const std::string& name, const std::string& password);
    int getID() const { return _ID; }
    std::string getName() const { return _name; }
    U32vec getPlayers() const { return _player; }
    RoomMode getRoomMode() const { return _mode; }
    bool isPasswordCorrect(const std::string& word) const { return _password=="" || _password==word; }
    bool isGameEnd() const { return _endgame; }
    virtual void startGame(std::vector<Deck&> deck)=0;
    virtual bool isFull() const =0;
    virtual bool addPlayer(uint32_t playerid)=0;
    virtual void endGame()=0;
    virtual uint32_t getWinnerID()=0;
    virtual uint32_t getLoserID()=0;
protected:
    uint32_t _ID;
    std::string _name;
    std::string _password;
    U32vec _player;
    RoomMode _mode;
    bool _endgame=false;
};


class OneOnOneRoom : public Room
{
public:
    OneOnOneRoom(uint32_t id, const std::string& name, const std::string& password, uint32_t playerid) : Room(id, name, password, playerid) { _mode = ONEONONE_ROOM; }
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(uint32_t playerid) override;
    void startGame(std::vector<Deck&> deck) override;
    void endGame() override;
    uint32_t getWinnerID() override;
    uint32_t getLoserID() override;
private:
    static constexpr short MaxPlayerNum=2;
};


class LadderRoom : public Room
{
public:
    LadderRoom(uint32_t id, const std::string& name, const std::string& password, uint32_t playerid) : Room(id, name, password, playerid) { _mode = LADDER_ROOM; }
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(uint32_t playerid) override;
    void startGame(std::vector<Deck&> deck) override;
    void endGame() override;
    uint32_t getWinnerID() override;
    uint32_t getLoserID() override;
private:
    static constexpr short MaxPlayerNum=2;
    int getWinnerScore();
    int getLoserScore();
};









/*
#ifndef PLAYER
#define PLAYER
class Player
{
public:
    Player(uint32_t id, std::string name, U32vec deck) : _ID(id), _name(name), _deck(deck){}
    uint32_t getID() const { return _ID; }
    std::string getName() const { return _name; }
    U32vec getDeck() const { return _deck; }
private:
    uint32_t _ID;
    std::string _name;
    U32vec _deck;
};
#endif // PLAYER

#ifndef ROOM
#define ROOM
enum RoomMode { SINGLE_ROOM=0, ONEONONE_ROOM, LADDER_ROOM, ROOMMODE_COUNT};
class Room
{
public:
    Room(int id, std::string name, std::string word, Player* player);
    ~Room();//TODO
    static Room* createRoom(Player* player, RoomMode mode, int id, std::string name, std::string password);
    int getID() const { return _ID; }
    std::string getName() const { return _name; }
    std::vector<Player*> getPlayers() const { return _player; }
    RoomMode getRoomMode() const { return _mode; }
    bool isPasswordCorrect(std::string word) const { return _password=="" || _password==word; }
    bool isGameEnd() const { return _endgame; }
    virtual void startGame(Reader *reader, Sender *sender)=0;
    virtual bool isFull() const =0;
    virtual bool addPlayer(Player* player)=0;
	virtual void endGame()=0;
    virtual uint32_t getWinnerID()=0;
    virtual uint32_t getLoserID()=0;
protected:
    int _ID;
    std::string _name;
    std::string _password;
    std::vector<Player*> _player;
    RoomMode _mode;
    bool _endgame=false;
    Desk* _desk;
};
class OneOnOneRoom : public Room
{
public:
    //~OneOnOneRoom() override; // TODO
    OneOnOneRoom(int id, std::string name, std::string word, Player* player) : Room(id, name, word, player) { _mode = ONEONONE_ROOM; }
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(Player* player) override;
	void startGame(Reader *reader, Sender *sender) override;
	void endGame() override;
	uint32_t getWinnerID() override;
	uint32_t getLoserID() override;
private:

    static constexpr short MaxPlayerNum=2;
};
class LadderRoom : public Room
{
public:
    LadderRoom(int id, std::string name, std::string word, Player* player) : Room(id, name, word, player) { _mode = LADDER_ROOM; }
    //~LadderRoom() override;//TODO
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(Player* player) override;
	void startGame(Reader *reader, Sender *sender) override;
	void endGame() override;
	uint32_t getWinnerID() override;
	uint32_t getLoserID() override;
private:
    static constexpr short MaxPlayerNum=2;
};
#endif // ROOM

#ifndef ARENA
#define ARENA
class Arena_
{
    friend std::ostream & operator << (std::ostream & os, const Arena_* arena);
public:
    Arena_(Reader *in, Sender *out, AccountSystem *acc);
    ~Arena_();
    ///建立房間，建立成功回傳id，-1:Failed，名稱重複
    int createRoom(uint32_t playerID, RoomMode mode, std::string name, std::string password);
    bool enterRoom(uint32_t playerID, RoomMode mode, int id, std::string password);
    void enterRoomRandom(uint32_t playerID, RoomMode mode);
    bool inviteFriend(uint32_t playerID, RoomMode mode, int id);
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
    int getNonRepeatRandomRoomID();
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
    enum ActionType { GET_ROOMLIST=0, GET_ROOMINFO, CREATE_ROOM, ENTER_ROOM, ENTER_ROOM_RANDOM, INVITE_FRIEND, ACTION_COUNT };
    std::string actionString[(int)ACTION_COUNT];//={"getRoomList", "getRoomInfo", "createRoom", "enterRoom", "enterRoomRandom", "inviteFriend"};
    void setJson(json& j);
    int getActionType(std::string action);
    void returnRoomList(RoomMode mode);
    void returnRoomInfo(RoomMode mode, int roomId);
    void returnCreateRoom(uint32_t playerID, RoomMode mode, std::string name, std::string password);
    void returnEnterRoom(uint32_t playerID, RoomMode mode, int id, std::string password);
    void start(Room* room, Reader* reader, Sender* sender);
};
#endif // ARENA
*/
#endif //ANOTHER_CARD_GAME_ACG_ROOM_H
