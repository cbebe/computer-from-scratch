#include "Parser.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "trim.h"

using std::string;

Parser::Parser(std::ifstream* in) : ins(in) {}

bool Parser::hasMoreCommands() { return !ins->eof(); }

void Parser::advance() {
    string currentLine;
    do {
        std::getline(*ins, currentLine);
        currentLine = trim(currentLine);
        // comments and empty lines are removed
    } while (currentLine.length() == 0);
    currentCommand = currentLine;
}

command Parser::commandType() { return A_COMMAND; }

string Parser::symbol() { return ""; }

string Parser::dest() { return ""; }

string Parser::comp() { return ""; }

string Parser::jump() { return ""; }

string Parser::getCommand() { return currentCommand; }