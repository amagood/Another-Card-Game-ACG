//
// Created by jacky on 2019/4/20.
//


#ifndef ANOTHER_CARD_GAME_ACG_ACGMAIN_H
#define ANOTHER_CARD_GAME_ACG_ACGMAIN_H

class Router;

class ACGMain {
private:
    Router *router;;
    bool isNotEnd = true;
public:
    ACGMain();
    void run();

};


#endif //ANOTHER_CARD_GAME_ACG_ACGMAIN_H