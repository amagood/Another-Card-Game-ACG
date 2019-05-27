#ifndef ANOTHER_CARD_GAME_ACG_ARENA_H
#define ANOTHER_CARD_GAME_ACG_ARENA_H

#include <iostream>
#include <vector>
#include <string>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "Router.h"
#include "Room.h"


enum ArenaAction { GET_ROOMLIST=0, GET_ROOMINFO, CREATE_ROOM, ENTER_ROOM, ENTER_ROOM_RANDOM, INVITE_FRIEND, START_GAME, ACTION_COUNT };
class Arena
{
public:
    Arena();
    ~Arena();
    uint32_t createRoom(uint32_t playerID, RoomMode mode, const std::string& name, const std::string& password="");
    bool enterRoom(uint32_t playerID, RoomMode mode, uint32_t id, const std::string& password);
    uint32_t enterRoomRandom(uint32_t playerID, RoomMode mode);
    bool inviteFriend(uint32_t playerID, RoomMode mode, uint32_t id);
    void startGame(RoomMode mode, uint32_t id);
    void getRoomList(RoomMode mode, U32vec idList, std::vector<std::string> nameList);
    void getRoomInfo(RoomMode mode, uint32_t id, std::string name, U32vec player);
    ArenaAction getAction(const std::string& action);
    nlohmann::json controlDesk(RoomMode mode, uint32_t id, nlohmann::json json);

private:
    AccountSystem* _account;
    std::vector<Room*> _room[ROOMMODE_COUNT];
    bool _running=true;
    static const char* _arenaActionString[];
    void _initArena();
    void _delAllRooms();
    bool _isRoomNameAdmitted(const std::string& name, RoomMode mode);
    uint32_t _getNonRepeatRandomRoomID();
    void _createRoom(uint32_t player, RoomMode mode, uint32_t id, const std::string& name, const std::string& password="");
    Room* _getRoom(RoomMode mode, uint32_t id);
    std::string _getRandomString(RoomMode mode);
    std::string _getNonRepeatRandomRoomName(RoomMode mode);
};
const char* Arena::_arenaActionString[] = {"getRoomList", "getRoomInfo", "createRoom", "enterRoom", "enterRoomRandom", "inviteFriend", "startGame"};
#endif //ANOTHER_CARD_GAME_ACG_ARENA_H
