#include <iostream>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "ArenaController.h"
#include "Arena.h"
#include "debug.h"

nlohmann::json ArenaController::run(nlohmann::json &json)
{
    error("ArenaController");

    nlohmann::json result = nlohmann::json();
    RoomMode mode = (RoomMode)json["roomMode"];
    if (json["eventType"]=="room")
    {
        nlohmann::json data = nlohmann::json();
        error(arena.getAction(json["action"]));
        switch(arena.getAction(json["action"]))
        {
            case GET_ROOMLIST:{
                U32vec idList;
                std::vector<std::string> nameList;
                arena.getRoomList(mode, idList, nameList);
                data["roomId"] = idList;
                error("GET_ROOMLIST");
            }break;
            case GET_ROOMINFO:{
                std::string name;
                U32vec player;
                arena.getRoomInfo(mode, json["roomId"], name, player);
                data["roomId"] = json["roomId"];
                data["roomName"] = name;
                data["playerId"] = player;
                error("GET_ROOMINFO");
            }break;
            case CREATE_ROOM:{
                uint32_t roomid = arena.createRoom(json["userId"], mode, json["roomName"], json["roomPassword"]);
                data["userId"] = json["userId"];
                data["roomId"] = roomid==-1?0:roomid;
                data["roomName"] = json["roomName"];
                error("CREATE_ROOM");
            }break;
            case ENTER_ROOM:{
                bool success = arena.enterRoom(json["userId"], mode, json["roomId"], json["roomPassword"]);
                data["result"] = (int)success;
                error("ENTER_ROOM");
            }break;
            case ENTER_ROOM_RANDOM:{
                uint32_t roomid = arena.enterRoomRandom(json["userId"], mode);
                data["userId"] = json["userId"];
                data["roomId"] = roomid;
                error("ENTER_ROOM_RANDOM");
            }break;
            case INVITE_FRIEND:{
                bool success = arena.inviteFriend(json["userId"], mode, json["roomId"]);
                data["result"] = (int)success;
                error("INVITE_FRIEND");
            }break;
            case START_GAME:{
                bool success = arena.startGame(mode, json["roomId"]);
                data["roomId"] = json["roomId"];
                data["result"] = (int)success;
                error("START_GAME");
            }break;
            default:
                break;
        }
        data["eventType"] = "room";
        data["roomMode"] = json["roomMode"];
        data["action"] = json["action"];
        result["data"] = data;
    } else {
        result = arena.controlDesk(mode, json["deskId"], json);
        error("DESK");
    }
    return result;
}