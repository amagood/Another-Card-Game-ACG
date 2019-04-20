//
// Created by jacky on 2019/4/20.
//

#ifndef ANOTHER_CARD_GAME_ACG_PAGECONTROLLER_H
#define ANOTHER_CARD_GAME_ACG_PAGECONTROLLER_H

#include "page/PageBase.h"
#include "page/MenuPage.h"
#include "page/LoginPage.h"
#include "page/PayMoneyPage.h"
#include "page/LobbyPage.h"
#include "page/DrawPage.h"
#include "page/DeckPage.h"
class PageController {
private:
    PageBase *pageNow = nullptr;
    string pageName = "";
public:
    void SetPage(PageBase *page) {
        PageBase *lastPage = pageNow;
        pageNow = &page;
        updatePage();
        delete lastPage;
    }
    void updatePage() {
        pageNow->updatePage();
        pageName = pageNow->getName();
    }
};


#endif //ANOTHER_CARD_GAME_ACG_PAGECONTROLLER_H
