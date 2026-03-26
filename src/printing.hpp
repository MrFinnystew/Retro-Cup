#pragma once

#include <iostream>

#include "color text.hpp"

using
std::cout,
std::endl,
std::string;

extern bool debugMode;

string toString(auto input) {
    return std::to_string(input);
}

void error(string errorMessage) {
    if (debugMode)
        cout << (startText+startBoldText+redText+endText) << errorMessage << resetText;
}

void warrning(string warrningMessage) {
    if (debugMode)
        cout << (startText+startBoldText+yellowText+endText) << warrningMessage << resetText;
}

void printInfo(string info) {
    if (debugMode)
        cout << (startText+startBlueText+endText) << info << resetText;
}

void importantInfo(string info) {
    if (debugMode)
        cout << (startText+startBoldText+greenText+endText) << info << resetText;
}

void printEndInfo(string info, auto value) {
    if (debugMode)
        cout << info << (startText+startBoldText+redText+endText) << value << (resetText) << endl;
}

void printBold(auto value) {
    if (debugMode)
        cout << (startText+startBoldText+endText) << value << (resetText);
}
