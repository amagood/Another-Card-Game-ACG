    //
// Created by jacky on 2019/4/20.
//

#include "ACGMain.h"
#include "Reader.h"
#include "Router.h"
#include "Printer.h"
#include <iostream>
void ACGMain::run() {

    while(isNotEnd) {
        nlohmann::json json = Reader::read();
        if (json.empty()) {

            std::cout << "123" << std::endl;
            continue;
        } else {
            std::cout << "eat successful" << std::endl;
            nlohmann::json out_json = router->run(json);
            Printer::print(out_json);
        }
    }
}
ACGMain::ACGMain() {
    router = new Router();
}
