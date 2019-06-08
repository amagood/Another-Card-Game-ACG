//
// Created by jacky on 2019/6/1.
//
#define DEBUG
#ifndef ANOTHER_CARD_GAME_ACG_DEBUG_H
#define ANOTHER_CARD_GAME_ACG_DEBUG_H
#ifdef DEBUG
#include<iostream>
using namespace std;
#define error(s) cout << s << endl
#else
#define error(s)
#endif
#endif //ANOTHER_CARD_GAME_ACG_DEBUG_H
