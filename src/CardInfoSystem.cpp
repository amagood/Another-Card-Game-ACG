//
// Created by jacky on 2019/5/21.
//

#include "CardInfoSystem.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "ACGType.h"
#include <iostream>
CardInfoSystem::CardInfoSystem() {
    load();
}

void CardInfoSystem::load() {
    std::string filename = "data/cardlist.json";
    std::ifstream file(filename);
    nlohmann::json jsonfile;
    jsonfile << file;
    cardlist = (std::vector<uint32_t >)jsonfile["cardlist"];
    std::cout << cardlist.size();


    for (uint32_t i : cardlist) {
        InfoCard card;
        std::string id_ = std::to_string(i);

        card.id = i;
        card.hp = jsonfile[id_]["hp"];
        card.mp = jsonfile[id_]["mp"];
        card.atk = jsonfile[id_]["atk"];
        card.name= jsonfile[id_]["name"];
        card.attribute = jsonfile[id_]["attribute"];
        infoCards.insert(std::make_pair(card.id, card));
    }
}

void CardInfoSystem::show() {
    for(auto i : infoCards) {
        std::cout << i.second.name;
    }
}

InfoCard * CardInfoSystem::getInfoCard(int id) {
    auto a = infoCards.find(id);
    return &(a->second);
}
int CardInfoSystem::getHp(int id) {
    return getInfoCard(id)->hp;
}
int CardInfoSystem::getMp(int id) {
    return getInfoCard(id)->mp;
}
int CardInfoSystem::getAtk(int id){
    return getInfoCard(id)->atk;
}
std::string CardInfoSystem::getName(int id) {
    return getInfoCard(id)->name;
}
std::string CardInfoSystem::getAttribute(int id) {
    return getInfoCard(id)->attribute;
}