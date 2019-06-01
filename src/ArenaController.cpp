#include <iostream>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "ArenaController.h"
#include "Arena.h"
#include "debug.h"

nlohmann::json ArenaController::run(nlohmann::json &j)
{
    error(123123123);

    nlohmann::json json = j["data"];
    nlohmann::json result = nlohmann::json();
    RoomMode mode = (RoomMode)json["roomMode"];
    if(json["eventType"]=="room")
    {
        nlohmann::json data = nlohmann::json();
        error(arena.getAction(json["action"]));
        switch(arena.getAction(json["action"]))
        {
            case GET_ROOMLIST:{
                U32vec idList;
                std::vector<std::string> nameList;
                arena.getRoomList(mode, idList, nameList);
                data["idList"] = idList;
                data["nameList"] = nameList;
                error("I am in")
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
                break;
        }
        data["eventType"] = "room";
        data["roomMode"] = json["roomMode"];
        data["action"] = json["action"];
        result["data"] = data;
    } else
        result = arena.controlDesk(mode, json["deskID"], json);
    return result;
}