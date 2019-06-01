//
// Created by jacky on 2019/4/21.
//

#include <iostream>
#include "Reader.h"
#include "debug.h"
nlohmann::json Reader::read()
{

    std::string line;
    std::getline(std::cin, line);
    try {
        return nlohmann::json::parse(line);
    }
    catch(nlohmann::json::parse_error &e) {
        error("parse error");
        return nlohmann::json();
    }
}
