//
// Created by jacky on 2019-05-17.
//

#include "Account.h"

Account::Account(std::string &id, std::string &password, uint32_t uuid) {
    id_ = id;
    password_ = password;
    user_id_ = uuid;
}
void Account::recordHistory(uint32_t rivalId, bool isWin, RoomMode r) {
    std::vector<int> game = {(int)rivalId, (int)isWin, (int)r};
    games ++;
    history.push_back(game);
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
    if(j.count("exp")!= 0) {
        exp = j["exp"];
    }
    if(j.count("level")!= 0) {
        level = j["level"];
    }
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
    j["history"] = history;
    j["exp"] = exp;
    j["level"] = level;
    return j;
}

void Account::modifyPassword(std::string password){
    password_ = password;
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
    if (money_ + money < 0) {
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
}
U32vec Account::getCards (){
    return card_list;
}
U32vec Account::getCards (uint32_t amount){
    U32vec s;
    for (uint32_t i = 0; i < amount && i < card_list.size(); i++) {
        s.push_back(card_list.at(i));
    }
    return s;
}
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

uint32_t Account::getLose() {
    return lose_;
}
uint32_t Account::getWin() {
    return win_;
}
std::string Account::getLadderLevel() {
    return ladderLevel;
}

void Account::win() {
    exp += 20;
    win_ += 1;
    updateLevel();
}
void Account::lose() {
    exp += 10;
    lose_ += 1;
    updateLevel();
}
void Account::ladderWin() {
    exp += 30;
    ladderPoint_ += 30;
    ladder_win_ += 1;
    win_ += 1;
    updateLevel();
}
void Account::ladderLose() {
    exp += 20;
    ladderPoint_ -= 20;
    ladder_lose_ += 1;
    lose_ += 1;
    updateLevel();
}

void Account::updateLevel() {
    if(exp<100) {
        level = 0;
    } else if (exp < 200) {
        level = 1;
    } else if (exp < 500) {
        level = 2;
    } else if (exp < 1000) {
        level = 3;
    } else if (exp < 2000) {
        level = 4;
    } else {
        level = 5;
    }
}