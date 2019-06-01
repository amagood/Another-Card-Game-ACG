#include <iostream>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "ArenaController.h"
#include "Arena.h"


nlohmann::json ArenaController::run(nlohmann::json json)
{
    nlohmann::json data;
    nlohmann::json result;
    RoomMode mode = (RoomMode)json["roomMode"];
    switch(arena.getAction(json["action"]))
    {
        case GET_ROOMLIST:{
            U32vec idList;
            std::vector<std::string> nameList;
            arena.getRoomList(mode, idList, nameList);
            data["idList"] = idList;
            data["nameList"] = nameList;
        }break;
        case GET_ROOMINFO:{
            std::string name;
            U32vec player;
            arena.getRoomInfo(mode, json["roomID"], name, player);
            data["roomID"] = json["roomID"];
            data["roomName"] = name;
            data["playerId"] = player;
        }break;
        case CREATE_ROOM:{
            uint32_t roomid = arena.createRoom(json["userId"], mode, json["name"], json["password"]);
            data["userId"] = json["userId"];
            data["roomId"] = roomid==-1?0:roomid;
            data["roomName"] = json["name"];
        }break;
        case ENTER_ROOM:{
            bool success = arena.enterRoom(json["userId"], mode, json["name"], json["password"]);
            data["result"] = (int)success;
        }break;
        case ENTER_ROOM_RANDOM:{
            uint32_t roomid = arena.enterRoomRandom(json["userId"], mode);
            data["userId"] = json["userId"];
            data["roomId"] = roomid;
        }break;
        case INVITE_FRIEND:{
            bool success = arena.inviteFriend(json["userId"], mode, json["roomID"]);
            data["result"] = (int)success;
        }break;
        case START_GAME:{
            arena.startGame(mode, json["roomID"]);
        }break;
        default:
            data = arena.controlDesk(mode, json["roomID"], json);
            break;
    }
    data["eventType"] = "room";
    data["roomMode"] = json["roomMode"];
    data["action"] = json["action"];
    result["data"] = data;
    return result;
}