#include "Parser.h"

#include <iostream>

#include "strhelp.h"

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
        lineNo++;
        // comments and empty lines are removed
        size_t commentPos = currentLine.find("//");

        if (found(commentPos)) currentLine = strBefore(currentLine, commentPos);
        currentLine = trimWhitespace(currentLine);

        foundCommand = !currentLine.empty();
    }
    currentCommand = currentLine;
}

string Parser::getCommand() { return currentCommand; }