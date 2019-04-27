//
// Created by jacky on 2019/4/20.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACGMAIN_H
#define ANOTHER_CARD_GAME_ACG_ACGMAIN_H

#include "AccountSystem.h"
#include "Reader.h"
#include "Printer.h"
#include "Router.h"
#include "LadderSystem.h"
class ACGMain {
private:
    AccountSystem * accountSystem;
    LadderSystem * ladderSystem;
    Reader * reader;
    Printer * printer;
    Router * router;
public:
    ACGMain();
    void run();
    void read();
    void print();
};


#endif //ANOTHER_CARD_GAME_ACG_ACGMAIN_H
