//
// Created by jacky on 2019/4/6.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
#define ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H

#include <vector>
#include <string>
class Account{
public:
    Account(std::string &id, std::string &password);
    bool is_same(Account &another);
    bool is_same_id(std::string& other_id);
    bool verify(std::string &password);
    void modify_password(std::string &password);
    void modify_money(int money);
    int get_money();
    std::string get_name(){return name;}
    int get_ladder_point(){return ladder_point;}
    int get_unique_num() { return u_num;}
private:
    int u_num = 0; // TODO make it unique, readonly
    int money_ = 0;
    int ladder_point = 0;
    std::string name;
    std::string id_;
    std::string password_;


};


class AccountSystem {

public:
    AccountSystem();
    bool create_account(std::string &id, std::string &password);
    bool exist(std::string &account_id);
    bool login(std::string &id, std::string &password);
    bool modify_password(std::string &id, std::string &ori_password, std::string &new_password);
    void modify_money(std::string &id, int money);
    int get_money(std::string &id);
private:
    std::vector<Account> account_vector;
    Account* get_account(std::string id);
};

#endif //ANOTHER_CARD_GAME_ACG_ACCOUNTSYSTEM_H
