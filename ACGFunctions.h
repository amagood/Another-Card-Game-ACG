//
// Created by jacky on 2019/5/11.
//

#ifndef ANOTHER_CARD_GAME_ACG_SLEEP_H
#define ANOTHER_CARD_GAME_ACG_SLEEP_H

#ifdef LINUX
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif
namespace ACGFunction {
    void sleep(int sleepMs){
    #ifdef LINUX
        usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
    #endif
    #ifdef WINDOWS
        Sleep(sleepMs);
    #endif
    }
}
#endif //ANOTHER_CARD_GAME_ACG_SLEEP_H
