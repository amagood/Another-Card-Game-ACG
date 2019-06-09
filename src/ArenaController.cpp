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
                std::string name, level;
                U32vec player;
                bool full, playing;
                bool success = arena.getRoomInfo(mode, json["roomId"], name, player, level, full, playing);
                data["roomId"] = json["roomId"];
                data["roomName"] = name;
                data["playerId"] = player;
                data["roomLevel"] = level;
                data["full"] = (int)full;
                data["playing"] = (int)playing;
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
                if(success)
                    data["roomId"] = json["roomId"];
                else
                    data["roomId"] = 0;
                data["result"] = (int)success;
                error("ENTER_ROOM");
            }break;
            case ENTER_ROOM_RANDOM:{
                uint32_t roomid = arena.enterRoomRandom(json["userId"], mode);
                data["roomId"] = roomid;
                data["result"] = (int)(roomid>0);
                error("ENTER_ROOM_RANDOM");
            }break;
            case LEAVE_ROOM:{
                bool success = arena.leaveRoom(json["userId"], mode, json["roomId"]);
                data["result"] = (int)success;
                error("ENTER_ROOM");
            }break;
            case INVITE_FRIEND:{
                bool success = arena.inviteFriend(json["userId"], mode, json["roomId"]);
                data["result"] = (int)success;
                error("INVITE_FRIEND");
            }break;
            case START_GAME:{
                error("Room " + std::to_string((uint32_t)json["roomId"]) + " start game!!");
                data["desk"] = {};
                bool success = arena.startGame(mode, json["roomId"], data["desk"]);
                data["roomId"] = json["roomId"];
                data["result"] = (int)success;
                error("END_GAME");
            }break;
            case END_GAME:{
                error("Room " + std::to_string((uint32_t)json["roomId"]) + " end game!!");
                uint32_t winner, loser;
                bool success = arena.endGame(mode, json["roomId"], winner, loser);
                data["roomId"] = json["roomId"];
                data["result"] = (int)success;
                data["winner"] = winner;
                data["loser"] = loser;
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