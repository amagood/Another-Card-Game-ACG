#include "Desk.h"
#include "Deck.h"
#include <vector>
#include <string>
#include <iostream>


#ifndef PLAYER
#define PLAYER
class Player
{
public:
    Player(int id, std::string name, Deck & deck) : _ID(id), _name(name), _deck(deck){}
    int getID() const { return _ID; }
    std::string getName() const { return _name; }
    Deck & getDeck() const { return _deck; }
private:
    int _ID;
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
    int getID() const { return _ID; }
    std::string getName() const { return _name; }
    std::vector<Player*> getPlayers() const { return _player; }
    RoomMode getRoomMode() const { return _mode; }
    bool isPasswordCorrect(std::string word) const { return _password=="" || _password==word; }
    void getRoomInfo() const {}
    virtual bool isFull() const =0;
    virtual bool addPlayer(Player* player)=0;
	virtual void startGame()=0;
	virtual bool invitePlayer(int id)=0;
protected:
    int _ID;
    std::string _name;
    std::string _password;
    std::vector<Player*> _player;
    RoomMode _mode;
    Player* getPlayerInfo(int id);
	virtual void sendGameResult()=0;
};
class OneOnOneRoom : public Room
{
public:
    OneOnOneRoom(int id, std::string name, std::string word, Player* player) : Room(id, name, word, player) { _mode = ONEONONE_ROOM; }
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(Player* player) override;
    bool invitePlayer(int id) override;
	void startGame() override;
private:
    static constexpr short MaxPlayerNum=2;
	void sendGameResult() override;
};
class LadderRoom : public Room
{
public:
    LadderRoom(int id, std::string name, std::string word, Player* player) : Room(id, name, word, player) { _mode = LADDER_ROOM; }
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(Player* player) override;
    bool invitePlayer(int id) override;
	void startGame() override;
private:
    static constexpr short MaxPlayerNum=2;
	void sendGameResult() override;
};
#endif // ROOM

#ifndef ARENA
#define ARENA
class Arena
{
    friend std::ostream & operator << (std::ostream & os, const Arena* arena);
public:
    Arena();
    ~Arena();
    ///建立房間，True:建立成功，False:名稱重複
    bool createRoom(int playerID, std::string playerName, Deck & playerDeck, RoomMode mode, std::string name, std::string password);
    bool enterRoom(int playerID, std::string playerName, Deck & playerDeck, RoomMode mode, int id, std::string password);
    void enterRoomRandom(int playerID, std::string playerName, Deck & playerDeck, RoomMode mode);
private:
    std::vector<Room*> _room[ROOMMODE_COUNT];
    const std::string myJsonType="room";
    void initArena();
    int getNonRepeatRandomRoomID(RoomMode mode);
    std::string getRandomString(RoomMode mode);
    std::string getNonRepeatRandomRoomName(RoomMode mode);
    void createRoom(Player* player, RoomMode mode, int id, std::string name, std::string password);
    Room* getRoom(RoomMode mode, int id);
    void freeAllRooms();
    bool isRoomNameAdmitted(std::string name, RoomMode mode);
};
#endif // ARENA

