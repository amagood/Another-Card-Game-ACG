#include <iostream>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "ArenaController.h"
#include "Arena.h"


ArenaController::ArenaController(AccountSystem *acc) : account(acc) , arena(Arena(acc))
{

}
nlohmann::json ArenaController::run(nlohmann::json json)
{
    nlohmann::json result;
    RoomMode mode = json["mode"];
    switch(arena.getAction(json["action"]))
    {
        case GET_ROOMLIST:{
            U32vec idList;
            std::vector<std::string> nameList;
            arena.getRoomList(mode, idList, nameList);
        }break;
        case GET_ROOMINFO:{
            std::string name;
            U32vec player;
            arena.getRoomInfo(mode, json["roomID"], name, player);
        }break;
        case CREATE_ROOM:{
            uint32_t roomid = arena.createRoom(json["playerID"], mode, json["name"], json["password"]);
        }break;
        case ENTER_ROOM:{
            bool success = arena.enterRoom(json["playerID"], mode, json["name"], json["password"]);
        }break;
        case ENTER_ROOM_RANDOM:{
            uint32_t roomid = arena.enterRoomRandom(json["playerID"], mode);
        }break;
        case INVITE_FRIEND:{
            bool success = arena.inviteFriend(json["playerID"], mode, json["roomID"]);
        }break;
        case START_GAME:{
            arena.startGame(mode, json["roomID"]);
        }break;
        default:
            result = arena.controlDesk(mode, json["roomID"], json);
            break;
    }
    return result;
}