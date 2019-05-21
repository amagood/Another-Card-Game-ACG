
add_library(
        ACGMain ACGMain.cpp Printer.cpp
        Reader.cpp AccountSystem.cpp Router.cpp
        LadderSystem.cpp AccountSystemParser.cpp
        AccountSystemController.cpp Account.cpp DrawCardSystem.cpp DrawCardSystem.h MoneySystem.cpp MoneySystem.h AccountSystemPackage.cpp AccountSystemPackage.h ACGIO.cpp ACGIO.h
        desk.h desk.cpp Deck.cpp Deck.h
        Room.h Room.cpp


        CardFactory.cpp CardFactory.h GameBuildingSystem.cpp GameBuildingSystem.h)

