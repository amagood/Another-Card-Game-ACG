//
// Created by jacky on 2019-05-11.
//

#include "AccountSystemController.h"
#include "debug.h"
#include "AccountSystemCommand.h"

nlohmann::json AccountSystemController::run(nlohmann::json &j) {
    error("AccountSystemController Run");
    uint32_t userID;
    nlohmann::json data;
    std::string func;
    try {
        userID = j["userId"];
        data = j["data"];
        func = data["function"];
        data["returnValue"] = nlohmann::json({});
        data["returnValue"]["success"] = (map_functions.count(func) > 0) &&
                (map_functions.at(func)->execute(data, userID));
        data.erase("params");
    } catch (nlohmann::json::parse_error &e){
        error(j);
        error("ERROR: Json error, nod userId or no data, or no function");
        data["returnValue"]["success"] = false;
    }
    j["data"] = data;
    return j;
}

AccountSystemController::AccountSystemController(AccountSystem * accountSystem1) {
    map_functions = {
        {"getAccountName", new GetAccountNameCommand(accountSystem1)},
        {"createAccount", new CreateAccountCommand(accountSystem1)},
        {"login", new LoginCommand(accountSystem1)},
        {"logout", new LogoutCommand(accountSystem1)},
        {"getAccountInfo", new GetAccountInfoCommand(accountSystem1)},
        {"payMoney", new PayMoneyCommand(accountSystem1)},
        {"drawCards", new DrawCardCommand(accountSystem1)},
        {"getCards", new GetCardsCommand(accountSystem1)},
        {"getDeck", new GetDeckCommand(accountSystem1)},
        {"getUserId", new GetUserIdCommand(accountSystem1)},
        {"addAllToDesk", new AddAllToDeckCommand(accountSystem1)},
        {"modifyCards", new ModifyCards(accountSystem1)}
    };
}
