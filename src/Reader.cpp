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
        nlohmann::json result = nlohmann::json::parse(line);
        error("parse successful");
        if (!result.is_object()) {
            throw std::invalid_argument( "not an object" );
        }
        error(result.size());
        return result;
    }
    catch(nlohmann::json::parse_error &) {
        error("parse error");
        return nlohmann::json();
    } catch (std::invalid_argument &){
        error("not an object");
        return nlohmann::json({});
    }
}
