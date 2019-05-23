//
// Created by jacky on 2019/5/21.
//

#include "CardInfoSystem.h"

#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>

CardInfoSystem::CardInfoSystem() {
    load();
}

U32vec CardInfoSystem::getCardPool() {
    return cardlist;
}
void CardInfoSystem::load() {
    std::string filename = "data/cardlist.json";
    std::ifstream file(filename);
    nlohmann::json json_;
    file >> json_;
    for (uint32_t i : json_["cardlist"]) {
        cardlist.push_back(i);
    }
    std::cout << cardlist.size();


    for (uint32_t i : cardlist) {
        InfoCard card;
        std::string id_ = std::to_string(i);

        card.id = i;
        card.hp = json_[id_]["hp"];
        card.mp = json_[id_]["mp"];
        card.atk = json_[id_]["atk"];
        card.name= json_[id_]["name"];
        card.attribute = json_[id_]["attribute"];
        infoCards.insert(std::make_pair(card.id, card));
    }
}

void CardInfoSystem::show() {
    for(auto &i : infoCards) {
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