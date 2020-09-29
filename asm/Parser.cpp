#include "Parser.h"

#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "trim.h"

using std::string;

namespace code_regex {
const string a = "@([A-Za-z0-9$.:_]*)";
const string c =
    "^[ \t]*(A?M?D?)?[ \t]*=?[ \t]*([!-]?[01AMD]|[AMD][ \t]*[-+&|][ "
    "\t]*[1AMD])[ \t]*(?:;[ \t]*(J(?:MP|EQ|[GNL]E|[LG]T)))?$";
const string l = "\\(([A-Za-z$.:_][A-Za-z0-9$.:_]*)\\)";
};  // namespace code_regex

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
        // comments and empty lines are removed
        currentLine = trimWhitespace(currentLine);
        unsigned long commentPos = currentLine.find("//");
        if (commentPos != string::npos) {
            currentLine.erase(commentPos, currentLine.length() - commentPos);
        }
        foundCommand = !currentLine.empty();
    }
    currentCommand = currentLine;
}

command Parser::commandType(unsigned long &lineNo) {
    std::regex Argx(code_regex::a);
    std::regex Crgx(code_regex::c);
    std::regex Lrgx(code_regex::l);
    std::vector<std::regex> typeRgx = {Argx, Crgx, Lrgx};

    // i is the command type where A = 0, C = 1, L = 2
    for (int i = 0; i < 2; ++i)
        if (std::regex_match(currentCommand, typeRgx[i]))
            return static_cast<command>(i);

    std::cout << "Invalid syntax at " << lineNo << "\n";
    exit(1);
}

string Parser::symbol() {
    std::regex rgx(code_regex::a);
    return "";
}

string Parser::dest() { return ""; }

string Parser::comp() { return ""; }

string Parser::jump() { return stringToken(currentCommand, ";"); }

string Parser::getCommand() { return currentCommand; }