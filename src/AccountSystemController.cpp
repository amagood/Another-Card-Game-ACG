//
// Created by jacky on 2019-05-11.
//

#include "AccountSystemController.h"

#include "DrawCardSystem.h"

AccountSystemController::AccountSystemController() {
    accountSystem = new AccountSystem();
    drawCardSystem = new DrawCardSystem();
}
AccountSystem* AccountSystemController::getAccountSystem() {
    return accountSystem;
}
std::mutex* AccountSystemController::getAccountSystemMutex() {
    return &accountSystemMutex;
}


void AccountSystemController::createAccount(std::string id, std::string password) {
    bool success = accountSystem->createAccount(id, password);
    // TODO
}
void AccountSystemController::getAccountsName(std::vector<uint32_t> userIds) {
    nlohmann::json ans;
    for (uint32_t& id : userIds) {
        std::string name = accountSystem->getAccountName(id);
        ans[id] = name;
    }
}
void AccountSystemController::login(std::string name, std::string password) {
    accountSystem->login(name, password);
}
void AccountSystemController::logout(uint32_t userId) {
    accountSystem->logout(userId);
}
void AccountSystemController::payMoney(uint32_t userId, int number) {
    accountSystem->modifyMoney(userId, number);
}

void AccountSystemController::drawCards(uint32_t userId, int card_amount) {
    for (int i = 0; i < card_amount; i++) {
        uint32_t cardId = drawCardSystem->drawCard();
        if (!accountSystem->addCard(userId, cardId)) {
            //Todo raise error
            return;
        }
    }
}
void AccountSystemController::getCards(uint32_t userId) {
    std::vector<uint32_t> cards = accountSystem->getCards(userId);
    accountSystem->getDeck(userId);
}
void AccountSystemController::modifyCards(uint32_t userId, std::vector<uint32_t> cards, std::vector<uint32_t> decks)
{
    accountSystem->updateCards(userId, cards, decks);
    accountSystem->getDeck(userId);
    accountSystem->getCards(userId);
}
void AccountSystemController::getAccountInfo(uint32_t userId) {


}