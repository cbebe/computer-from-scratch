#include "Parser.h"

#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "trim.h"

using std::string;

Parser::Parser(const string &filename) {
    in.open(filename);
    if (in.fail()) {
        std::cout << filename << " not found.\n";
        exit(1);
    }
}

bool Parser::hasMoreCommands() { return !in.eof(); }

void Parser::advance(unsigned long &lineNo) {
    string currentLine;
    bool foundCommand = false;
    while (!foundCommand && std::getline(in, currentLine)) {
        currentLine = trimWhitespace(currentLine);
        // comments and empty lines are removed
    }
    currentCommand = currentLine;
}

command Parser::commandType(unsigned long &lineNo) {
    std::regex Argx("@([^0-9][A-Za-z0-9$.:_]*)");
    std::regex Crgx(
        "^([A|D|M]{1,3})? *=? *([01DAM+!&|]*) *;? *(J[MGLE][TEQP])?$");
    std::regex Lrgx("\(([^0-9][A-Za-z0-9$.:_]*)\)");
    std::vector<std::regex> typeRgx = {Argx, Crgx, Lrgx};

    // i is the command type where A = 0, C = 1, L = 2
    for (int i = 0; i < 2; ++i)
        if (std::regex_match(currentCommand, typeRgx[i]))
            return static_cast<command>(i);

    std::cout << "Invalid syntax at " << lineNo << "\n";
    exit(1);
}

string Parser::symbol() { return ""; }

string Parser::dest() { return ""; }

string Parser::comp() { return ""; }

string Parser::jump() { return stringToken(currentCommand, ";"); }

string Parser::getCommand() { return currentCommand; }