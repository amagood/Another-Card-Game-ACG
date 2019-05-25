    //
// Created by jacky on 2019/4/20.
//

#include "ACGMain.h"
#include "Reader.h"
#include "Router.h"
#include "Printer.h"

void ACGMain::run() {

    while(isEnd) {
        nlohmann::json json = Reader::read();
        if (json.empty()) {
            continue;
        } else {
            nlohmann::json out_json = router->run(json);
            Printer::print(json);
        }
    }
}
ACGMain::ACGMain() {
    router = new Router();
}
