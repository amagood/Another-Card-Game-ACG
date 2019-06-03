//
// Created by jacky on 2019-05-17.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNT_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNT_H


#include <nlohmann/json.hpp>

#include "ACGType.h"
#include "roommode.h"

class Account{
public:
    Account(std::string &id, std::string &password, uint32_t uuid);
    Account(nlohmann::json json);

    bool isSame(Account &another);
    bool isIDSame(std::string other_id);
    bool verify(std::string password);

    void modifyPassword(std::string password);
    bool modifyMoney(int money);
    nlohmann::json toJson();
    int getMoney();
    std::string getName();
    int getLadderPoint();
    uint32_t getUniqueNumber();
    U32vec getDeck ();
    U32vec getCards ();
    U32vec getCards (uint32_t amount);
    uint32_t getWin();
    uint32_t getLose();
    std::string getLadderLevel();
    bool addCard(uint32_t);
    void setDeck(U32vec deck);
    void setCards(U32vec cards);
    void left();
    void login();
    bool isOnline();
    void win();
    void lose();
    void ladderWin();
    void ladderLose();
    void recordHistory(uint32_t rivalId, bool isWin, RoomMode r);
    uint32_t getUUID() {return user_id_;}
private:
    uint32_t user_id_ = 0; // TODO make it unique, readonly
    int money_ = 0;
    bool online = false;
    std::string id_;
    std::string password_;
    uint32_t win_ = 0;
    uint32_t lose_ = 0;

    int ladderPoint_ = 0;
    std::string ladderLevel = "copper";
    uint32_t ladder_win_ = 0;
    uint32_t ladder_lose_ = 0;
    U32vec deck_card_list;
    U32vec card_list;
    int games = 0;
    std::vector<std::vector<int> > history;

};

#endif //ANOTHER_CARD_GAME_ACG_ACCOUNT_H
