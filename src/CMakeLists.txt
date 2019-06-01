
add_library(ACGMain ACGMain.cpp
        #AccountSystem
        AccountSystem.cpp Account.cpp AccountSystemController.cpp
        LadderSystem.cpp
        DrawCardSystem.cpp CardInfoSystem.cpp
        MoneySystem.cpp
        #ACGIO
        Printer.cpp Reader.cpp Router.cpp
        #Room
        ArenaController.cpp Arena.cpp Room.cpp
        #GameSystem
        CardFactory.cpp GameBuildingSystem.cpp
        )

