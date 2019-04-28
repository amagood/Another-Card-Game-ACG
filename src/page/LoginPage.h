//
// Created by jacky on 2019/4/20.
//

#ifndef ANOTHER_CARD_GAME_ACG_LOGINPAGE_H
#define ANOTHER_CARD_GAME_ACG_LOGINPAGE_H

class LoginPage {
public:
    void createAccount(string id, string pwd);
    void login(string id, string pwd);
private:
    void gotoMenuPage();
};


#endif //ANOTHER_CARD_GAME_ACG_LOGINPAGE_H
