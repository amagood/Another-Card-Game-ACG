//
// Created by jacky on 2019-05-17.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNT_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNT_H

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

typedef std::vector<uint32_t> U32vec;

class Account{
public:
    Account(std::string &id, std::string &password);
    Account(nlohmann::json json);

    bool isSame(Account &another);
    bool isIDSame(std::string &other_id);
    bool verify(std::string &password);

    void modifyPassword(std::string &password);
    void modifyMoney(int money);
    nlohmann::json toJson();
    int getMoney();
    std::string getName(){return name_;}
    std::string getDeviceId();
    int getLadderPoint(){return ladderPoint_;}
    uint32_t getUniqueNumber() { return user_id_;}
    U32vec getDeck (){
        return deck_card_list;
    };
    U32vec getCards (){
        return card_list;
    };
    void setDeck(U32vec deck) {
        deck_card_list = deck;
    }
    void setCards(U32vec cards) {
        card_list = cards;
    }
    void left(){
        online = false;
    }
    void login() {
        online = true;
    }
    bool isOnline() {
        return online;
    }
private:
    uint32_t user_id_ = 0; // TODO make it unique, readonly
    int money_ = 0;
    std::string name_;
    bool online = false;
    std::string id_;
    std::string password_;
    std::string device_id_;


    uint32_t win_ = 0;
    uint32_t lose_ = 0;


    int ladderPoint_ = 0;
    std::string ladderLevel = "copper";
    uint32_t ladder_win_;
    uint32_t ladder_lose_;
    // FIXME should add some interact with card and card list
    U32vec deck_card_list;
    U32vec card_list;
    // FIXME should add history

};

#endif //ANOTHER_CARD_GAME_ACG_ACCOUNT_H
