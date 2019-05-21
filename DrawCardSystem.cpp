//
// Created by jacky on 2019-05-17.
//

#include "DrawCardSystem.h"

#include <ctime>
#include <cstdlib>
#include <fstream>

#include <nlohmann/json.hpp>

DrawCardSystem::DrawCardSystem() {
    load();
}

void DrawCardSystem::load() {
    nlohmann::json jsonfile;
    std::ifstream file("data/cardlist.json");
    jsonfile << file;
    ///FIXME
    ///cardpools = (std::vector<uint32_t >)jsonfile["cardlist"];

}
uint32_t DrawCardSystem::drawCard() {
    uint32_t number = rand() % cardpools.size();
    return cardpools.at(number);
}
