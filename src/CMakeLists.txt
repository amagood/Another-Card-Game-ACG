
add_library(ACGMain ACGMain.cpp)
add_library(ACGIO ACGIO.cpp Printer.cpp Reader.cpp Router.cpp Sender.cpp AccountSystemParser.cpp)
add_library(AccountSystem AccountSystem.cpp Account.cpp AccountSystemController.cpp
        LadderSystem.cpp
        DrawCardSystem.cpp CardInfoSystem.cpp
        MoneySystem.cpp ArenaController.cpp ArenaController.h Arena.cpp Arena.h)
add_library(Room Room.cpp)
add_library(GameSystem CardFactory.cpp GameBuildingSystem.cpp desk.cpp Deck.cpp cards.cpp)