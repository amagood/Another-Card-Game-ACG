//
// Created by jacky on 2019-05-17.
//

#include "Account.h"

Account::Account(std::string &id, std::string &password, uint32_t uuid) {
    id_ = id;
    password_ = password;
    user_id_ = uuid;
}
Account::Account(nlohmann::json j) {
    user_id_ = j["userId"];
    id_ = j["name"];
    password_ = j["password"];
    win_ = j["win"];
    lose_ = j["lose"];
    ladderPoint_ = j["ladderPoint"];
    std::vector<uint32_t > d = j["deck"];
    std::vector<uint32_t > c = j["cards"];
    ladderLevel = j["ladderLevel"];
    ladder_win_ = j["ladderWin"];
    ladder_lose_ = j["ladderLose"];
    deck_card_list = d;
    card_list = c;
}
nlohmann::json Account::toJson() {
    nlohmann::json j;
    j["userId"] = user_id_;
    j["name"] = id_;
    j["password"] = password_;
    j["win"] = win_ ;
    j["lose"] = lose_;
    j["ladderPoint"] = ladderPoint_;
    j["deck"] = deck_card_list;
    j["cards"] = card_list;
    j["ladderLevel"] = ladderLevel;
    j["ladderWin"] = ladder_win_;
    j["ladderLose"]= ladder_lose_;
    return j;
}

void Account::modifyPassword(std::string password){
    password_ = password;
}
std::string Account::getDeviceId() {
    return device_id_;
}
bool Account::isIDSame(std::string other_id) {
    return this->id_ == other_id;
}
bool Account::isSame(Account &another) {
    return this->isIDSame(another.id_);
}
int Account::getMoney() {
    return money_;
}
bool Account::modifyMoney(int money) {
    if (money < 0) {
        return false;
    } else {
        money_ += money;
        return true;
    }
}
std::string Account::getName() {
    return id_;
}

int Account::getLadderPoint(){
    return ladderPoint_;
}

uint32_t Account::getUniqueNumber() {
    return user_id_;
}

U32vec Account::getDeck (){
    return deck_card_list;
};
U32vec Account::getCards (){
    return card_list;
};
void Account::setDeck(U32vec deck) {
    deck_card_list = deck;
}
void Account::setCards(U32vec cards) {
    card_list = cards;
}
void Account::left(){
    online = false;
}
void Account::login() {
    online = true;
}
bool Account::isOnline() {
    return online;
}
bool Account::addCard(uint32_t card_num) {
    card_list.push_back(card_num);
    return true;
}