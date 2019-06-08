#ifndef ANOTHER_CARD_GAME_ACG_ARENA_H
#define ANOTHER_CARD_GAME_ACG_ARENA_H

#include <iostream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "Room.h"
#include "roommode.h"

enum ArenaAction { GET_ROOMLIST=0, GET_ROOMINFO, CREATE_ROOM, ENTER_ROOM, ENTER_ROOM_RANDOM, INVITE_FRIEND, START_GAME, END_GAME, ACTION_COUNT };
class Arena
{
public:
    Arena(AccountSystem* account);
    ~Arena();
    uint32_t createRoom(uint32_t playerID, RoomMode mode, std::string name, std::string password="");
    bool enterRoom(uint32_t playerID, RoomMode mode, uint32_t id, const std::string& password);
    uint32_t enterRoomRandom(uint32_t playerID, RoomMode mode);
    bool inviteFriend(uint32_t playerID, RoomMode mode, uint32_t id);
    bool startGame(RoomMode mode, uint32_t id);
    void getRoomList(RoomMode mode, U32vec &idList, std::vector<std::string> &nameList);
    bool getRoomInfo(RoomMode mode, uint32_t id, std::string &name, U32vec &player, std::string &level);
    static ArenaAction getAction(const std::string& action);
    nlohmann::json controlDesk(RoomMode mode, uint32_t id, nlohmann::json json);
    bool endGame(RoomMode mode, uint32_t id, uint32_t& winner, uint32_t& loser);

private:
    AccountSystem* _account;
    std::vector<Room*> _room[ROOMMODE_COUNT];
    static const char* _arenaActionString[];
    void _initArena();
    void _delAllRooms();
    bool _isRoomNameAdmitted(const std::string& name, RoomMode mode);
    uint32_t _getNonRepeatRandomRoomID();
    void _createRoom(uint32_t player, RoomMode mode, uint32_t id, std::string name, std::string password="");
    Room* _getRoom(RoomMode mode, uint32_t id);
    int _getRoomIndex(RoomMode mode, uint32_t id);
    std::string _getRandomString(RoomMode mode);
    std::string _getNonRepeatRandomRoomName(RoomMode mode);
};
#endif //ANOTHER_CARD_GAME_ACG_ARENA_H
