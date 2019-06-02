//
// Created by jacky on 2019/6/3.
//

#include "usefulCalls.h"
#include "CardInfoSystem.h"

UsefulCalls::UsefulCalls() {
    cardInfoSystem = new CardInfoSystem();
}

nlohmann::json UsefulCalls::run(nlohmann::json j) {
    if (j["data"]["function"] == "getCardInfo") {
        uint32_t cardId = j["data"]["params"][0];
        InfoCard * infoCard =cardInfoSystem->getInfoCard(cardId);
        j["data"]["card"] = nlohmann::json({});
        j["data"]["card"]["name"] = infoCard->name;
        j["data"]["card"]["attri"] = infoCard->attribute;
        j["data"]["card"]["mp"] = infoCard->mp;
        j["data"]["card"]["hp"] = infoCard->hp;
        j["data"]["card"]["atk"] = infoCard->atk;
        j["data"]["card"]["id"] = infoCard->id;
        return j;
    } else {
        return nlohmann::json();
    }
}