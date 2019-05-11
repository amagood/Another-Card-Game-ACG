//
// Created by jacky on 2019-05-11.
//

#include "AccountSystemParser.h"
#include "AccountSystem.h"

void AccountSystemParser::setIOQueue(std::queue<nlohmann::json> &in, std::mutex &in_mutex) {
    in_json_queue_ = &in;
    in_mutex_ = &in_mutex;
}
void AccountSystemParser::setAccountSystemController(AccountSystemController *accountSystemController) {
    accountSystemController_ = accountSystemController;
}

void AccountSystemParser::parse() {
    if (accountSystemController_ == nullptr) {
        throw std::runtime_error("AccountSystem is nullptr");
    } else if (in_json_queue_ == nullptr || in_mutex_) {
        throw std::runtime_error("json queue or mutex is nullptr");
    }
    while (!stop_parse) {
        in_mutex_->lock();
        if (in_json_queue_->empty()){
            in_mutex_->unlock();
            continue;
        }
        nlohmann::json j = in_json_queue_->front();
        in_json_queue_->pop();
        in_mutex_->unlock();
        uint32_t userID = j["userId"];
        nlohmann::json data = j["data"];
        std::string func = data["function"];

        if(func == "getAccountName") {
            std::vector<int> params = data["params"];
            accountSystemController_->getAccountName(params);

        } else if(func == "createAccount") {
            std::vector<std::string> params = data["params"];
            accountSystemController_->createAccount(params[0], params[1]);
        } else if(func == "login") {
            std::vector<std::string> params = data["params"];
            accountSystemController_->login(params[0], params[1]);
        } else if (func == "getAccountInfo") {
            std::vector<int> params = data["params"];
            accountSystemController_->getAccountInfo(params[0]);
        } else if (func == "logout") {
            std::vector<int> params = data["params"];
            accountSystemController_->logout(params[0]);
        } else if (func == "payMoney") {
            std::vector<int> params = data["params"];
            accountSystemController_->payMoney(userID, params[0]);
        } else if (func == "drawCards") {
            std::vector<int> params = data["params"];
            accountSystemController_->drawCards(userID, params[0]);
        } else if (func == "getCards") {
            std::vector<int> params = data["params"];
            accountSystemController_->getCards(params[0]);

        } else if (func == "modifyCards") {
            std::vector<int> params = data["params"];
            std::vector<uint32_t> cards = data["paramsMap"]["cards"];
            std::vector<uint32_t> deck = data["paramsMap"]["deck"];
            accountSystemController_->modifyCards(params[0], cards, deck);
        }

    }
}