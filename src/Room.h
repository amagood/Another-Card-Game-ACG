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
    static nlohmann::json deskAction(nlohmann::json json);
    static RoomMode getMode(const std::string& mode);
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
private:
    static const char* _roomModeString[];
};
const char* Room::_roomModeString[] = {"SingleRoom", "OneOnOneRoom", "LadderRoom"};


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
#endif //ANOTHER_CARD_GAME_ACG_ROOM_H