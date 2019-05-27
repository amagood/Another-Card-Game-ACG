#ifndef ANOTHER_CARD_GAME_ACG_ARENA_H
#define ANOTHER_CARD_GAME_ACG_ARENA_H

#include <iostream>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "Router.h"
#include "Room.h"

class Arena
{
public:
    Arena();
    ~Arena();
    int createRoom(uint32_t playerID, RoomMode mode, const std::string& name, const std::string& password="");
    bool enterRoom(uint32_t playerID, RoomMode mode, uint32_t id, const std::string& password);
    void enterRoomRandom(uint32_t playerID, RoomMode mode);
    bool inviteFriend(uint32_t playerID, RoomMode mode, uint32_t id);
    void startGame(RoomMode mode, uint32_t id);

private:
    AccountSystem* _account;
    std::vector<Room*> _room[ROOMMODE_COUNT];
    bool _running=true;
    void _initArena();
    void _delAllRooms();
    bool _isRoomNameAdmitted(const std::string& name, RoomMode mode);
    uint32_t _getNonRepeatRandomRoomID();
    void _createRoom(uint32_t player, RoomMode mode, uint32_t id, const std::string& name, const std::string& password="");
    Room* _getRoom(RoomMode mode, uint32_t id);
    std::string _getRandomString(RoomMode mode);
    std::string _getNonRepeatRandomRoomName(RoomMode mode);

};



#endif //ANOTHER_CARD_GAME_ACG_ARENA_H
