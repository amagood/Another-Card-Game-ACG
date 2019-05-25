//
// Created by jacky on 2019/4/21.
//

#include "Printer.h"
#include <nlohmann/json.hpp>
#include <iostream>

void Printer::print(nlohmann::json &j) {
    std::cout << j << std::endl;
}
