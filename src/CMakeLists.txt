
add_library(ACGMain ACGMain.cpp
        #AccountSystem
        AccountSystem.cpp Account.cpp AccountSystemController.cpp
        DrawCardSystem.cpp CardInfoSystem.cpp
        #ACGIO
        Printer.cpp Reader.cpp Router.cpp
        #Room
        ArenaController.cpp Arena.cpp Room.cpp
        #GameSystem
        CardFactory.cpp GameBuildingSystem.cpp
        DeskController.cpp
        cards.cpp
        #desk.cpp
        NDesk.cpp
        Deck.cpp
        usefulCalls.cpp
        )

