//
// Created by jacky on 2019-05-17.
//

#include "Account.h"

Account::Account(std::string &id, std::string &password) {
    id_ = id;
    password_ = password;
}
Account::Account(nlohmann::json j) {
    user_id_ = j["userId"];
    name_ = j["name"];
    password_ = j["password"];
    win_ = j["win"];
    lose_ = j["lose"];
    ladderPoint_ = j["ladderPoint"];
    std::vector<uint32_t > d = j["deck"];
    std::vector<uint32_t > c = j["cards"];
    ladderLevel = j["ladderLevel"];
    deck_card_list = d;
    card_list = c;
}
nlohmann::json Account::toJson() {
    nlohmann::json j;
    j["userId"] = user_id_;
    j["name"] = name_;
    j["password"] = password_;
    j["win"] = win_ ;
    j["lose"] = lose_;
    j["ladderPoint"] = ladderPoint_;
    j["deck"] = deck_card_list;
    j["cards"] = card_list;
    j["ladderLevel"] = ladderLevel;
    return j;
}

void Account::modifyPassword(std::string &password){
    password_ = password;
}
std::string Account::getDeviceId() {
    return device_id_;
}
bool Account::isIDSame(std::string &other_id) {
    return this->id_ == other_id;
}
bool Account::isSame(Account &another) {
    return this->isIDSame(another.id_);
}
int Account::getMoney() {
    return money_;
}
void Account::modifyMoney(int money) {
    money_ += money;
}
