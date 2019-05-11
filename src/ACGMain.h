//
// Created by jacky on 2019/4/20.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACGMAIN_H
#define ANOTHER_CARD_GAME_ACG_ACGMAIN_H


#include "AccountSystemController.h"

#include "Reader.h"
#include "Printer.h"
#include "Router.h"

class ACGMain {
private:

    AccountSystemController *accountSystemController;
    Reader * reader;
    Printer * printer;
    Router * router;
    void read();
    void print();
    void route();
public:
    ACGMain();
    void run();

};


#endif //ANOTHER_CARD_GAME_ACG_ACGMAIN_H
