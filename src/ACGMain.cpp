    //
// Created by jacky on 2019/4/20.
//

#include "ACGMain.h"
#include "Reader.h"
#include "Router.h"
#include "Printer.h"
#include <iostream>
#include "debug.h"
void ACGMain::run() {

    while(isNotEnd) {
        nlohmann::json json = Reader::read();

        if (json.empty()) {
            error("json is empty");
            continue;
        } else {
            error("eat successful");
            if (json["data"]["eventType"] == "ENDING") {
                isNotEnd = false;
                router->end();
                break;
            }
            nlohmann::json out_json = router->run(json);
            Printer::print(out_json);
        }
    }

}
ACGMain::ACGMain() {
    router = new Router();
}
