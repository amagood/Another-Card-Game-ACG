//
// Created by jacky on 2019/4/21.
//

#include "Printer.h"
#include <nlohmann/json.hpp>
#include "time.h"
#include <iostream>

void Printer::print(nlohmann::json &j) {
    j["time"] = time(nullptr);
    std::cout << j << std::endl;
}
