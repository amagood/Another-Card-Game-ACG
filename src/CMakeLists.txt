
add_library(ACGMain ACGMain.cpp)
add_library(ACGIO Printer.cpp Reader.cpp Router.cpp)
add_library(AccountSystem AccountSystem.cpp Account.cpp AccountSystemController.cpp
        LadderSystem.cpp
        DrawCardSystem.cpp CardInfoSystem.cpp
        MoneySystem.cpp)
add_library(Room ArenaController.cpp Arena.cpp Room.cpp)
add_library(GameSystem CardFactory.cpp GameBuildingSystem.cpp)