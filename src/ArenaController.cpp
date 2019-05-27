#include <iostream>

#include <nlohmann/json.hpp>

#include "AccountSystem.h"
#include "Router.h"
#include "ArenaController.h"
#include "Arena.h"

ArenaController::ArenaController(AccountSystem * acc)
{
    account = acc;
    arena = Arena();
}
nlohmann::json run(nlohmann::json json)
{
    nlohmann::json result;



    return result;
}
