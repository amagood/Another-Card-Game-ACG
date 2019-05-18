//
// Created by jacky on 2019/4/20.
//

#ifndef ANOTHER_CARD_GAME_ACG_ACGMAIN_H
#define ANOTHER_CARD_GAME_ACG_ACGMAIN_H


#include "AccountSystemController.h"

#include "Reader.h"
#include "Printer.h"
#include "Router.h"
#include "ACGIO.h"

class ACGMain {
private:
    ACGIO * acgio;
    Router * router;
    AccountSystemController * accountSystemController;
    void acgio_run();
public:
    ACGMain();
    void run();

};


#endif //ANOTHER_CARD_GAME_ACG_ACGMAIN_H
