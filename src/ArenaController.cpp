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
                std::string level;
                U32vec player;
                bool success = arena.getRoomInfo(mode, json["roomId"], name, player, level);
                data["roomId"] = json["roomId"];
                data["roomName"] = name;
                data["playerId"] = player;
                data["roomLevel"] = level;
                data["result"] = (int)success;
                error("GET_ROOMINFO");
            }break;
            case CREATE_ROOM:{
                uint32_t roomid = arena.createRoom(json["userId"], mode, json["roomName"], json["roomPassword"]);
                data["userId"] = json["userId"];
                data["roomId"] = roomid==-1?0:roomid;
                data["roomName"] = json["roomName"];
                data["result"] = (int)(roomid>0);
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
                data["result"] = (int)(roomid>0);
                error("ENTER_ROOM_RANDOM");
            }break;
            case INVITE_FRIEND:{
                bool success = arena.inviteFriend(json["userId"], mode, json["roomId"]);
                data["result"] = (int)success;
                error("INVITE_FRIEND");
            }break;
            case START_GAME:{
                error(json["roomId"]);
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
        result["data"] = arena.controlDesk(mode, json["deskId"], json);
        result["data"]["eventType"] = "desk";
        error("DESK");
    }
    return result;
}