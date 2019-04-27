//
// Created by jacky on 2019/4/21.
//

#include "Router.h"

#include <queue>

#include "nlohmann/json.hpp"

#include "Reader.h"
#include "Printer.h"

Router::Router() = default;

Printer* Router::buildPrinter() {
    return new Printer(toPrint, printMutex);
}
Reader* Router::buildReader() {
    return new Reader(toDeliver, readMutex);
}