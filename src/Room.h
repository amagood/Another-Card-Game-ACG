#ifndef ANOTHER_CARD_GAME_ACG_ROOM_H
#define ANOTHER_CARD_GAME_ACG_ROOM_H

#include <iostream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>

#include "Deck.h"
#include "AccountSystem.h"
#include "DeskController.h"
#include "roommode.h"

class Room
{
public:
    Room(uint32_t id, const std::string& name, const std::string& password, uint32_t playerid);
    ~Room();//TODO
    nlohmann::json deskAction(nlohmann::json json);
    static RoomMode getMode(const std::string& mode);
    static Room* createRoom(uint32_t player, RoomMode mode, uint32_t id, const std::string& name, const std::string& password, const std::string& level="");
    int getID() const { return _ID; }
    std::string getName() const { return _name; }
    U32vec getPlayers() const { return _player; }
    virtual const std::string getLevel() const =0;
    RoomMode getRoomMode() const { return _mode; }
    bool isEnd() { return _deskController.winer_and_endgame()>=0;}
    bool isPlaying() { return _playing; }
    bool isPasswordCorrect(const std::string& word) const { return _password=="" || _password==word; }
    virtual nlohmann::json startGame(std::vector<U32vec> deck)=0;
    virtual bool isFull() const =0;
    virtual bool addPlayer(uint32_t playerid, const std::string& level="")=0;
    void endGame();
    uint32_t getWinnerID() { return _player[_winner];}
    uint32_t getLoserID() { return _player[_loser];}
protected:
    uint32_t _ID;
    std::string _name;
    std::string _password;
    U32vec _player;
    RoomMode _mode;
    DeskController _deskController;
    bool _playing=false;
    short _winner;
    short _loser;

private:
    static const char* _roomModeString[];
};


class OneOnOneRoom : public Room
{
public:
    OneOnOneRoom(uint32_t id, const std::string& name, const std::string& password, uint32_t playerid) : Room(id, name, password, playerid) { _mode = ONEONONE_ROOM; }
    const std::string getLevel() const override { return ""; }
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(uint32_t playerid, const std::string& level) override;
    nlohmann::json startGame(std::vector<U32vec> deck) override;
private:
    static constexpr short MaxPlayerNum=2;
};


class LadderRoom : public Room
{
public:
    LadderRoom(uint32_t id, const std::string& name, const std::string& password, uint32_t playerid, const std::string& level) : Room(id, name, password, playerid), _level(level) { _mode = LADDER_ROOM; }
    const std::string getLevel() const override { return _level; }
    bool isFull() const override { return _player.size()>=MaxPlayerNum; }
    bool addPlayer(uint32_t playerid, const std::string& level) override;
    nlohmann::json startGame(std::vector<U32vec> deck) override;
private:
    static constexpr short MaxPlayerNum=2;
    const std::string _level;
    int getWinnerScore();
    int getLoserScore();
};

#endif //ANOTHER_CARD_GAME_ACG_ROOM_H
