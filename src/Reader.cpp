//
// Created by jacky on 2019/4/21.
//

#include <iostream>
#include <nlohmann/json.hpp>
#include <Reader.h>

nlohmann::json Reader::read()
{

    std::string line;
    std::getline(std::cin, line);
    try {
        return nlohmann::json::parse(line);
    }
    catch(nlohmann::json::parse_error &e) {
        return nlohmann::json();
    }
}
