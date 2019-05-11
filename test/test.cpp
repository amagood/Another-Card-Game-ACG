//
// Created by jacky on 2019-05-11.
//
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using json = nlohmann::json;
int main()
{
    json jsonfile;
    std::ifstream file("testCase/login.json");

    jsonfile << file;
    json json2 = jsonfile["data"]["s"];
    int i = json2["data"]["params"][0];
    cout << i;
    vector<string> j = json2;
    cout << j[0];
    cout << j[1];
    cout << j[2];
    return 0;
}