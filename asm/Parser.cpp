#include "Parser.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "strhelp.h"

using std::string;

std::unordered_map<char, command> commandTable{
    {'@', A_COM}, {'A', C_COM}, {'D', C_COM}, {'M', C_COM}, {'0', C_COM},
    {'1', C_COM}, {'-', C_COM}, {'!', C_COM}, {'(', L_COM}};

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
        if (found(commentPos)) {
            currentLine.erase(commentPos, currentLine.length() - commentPos);
        }
        foundCommand = !currentLine.empty();
    }
    currentCommand = currentLine;
}

command Parser::commandType(unsigned long &lineNo) {
    if (commandTable.find(currentCommand[0]) != commandTable.end())
        return commandTable[currentCommand[0]];

    std::cout << "Invalid syntax at " << lineNo << "\n";
    exit(1);
}

string Parser::symbol() {
    if (currentCommand[0] == '@') return strAfter(currentCommand, 0);

    unsigned int openParens = currentCommand.find('(');
    unsigned int closedParens = currentCommand.find(')');

    if (found(openParens) && found(closedParens))
        return strBetween(currentCommand, openParens, closedParens);

    return "";
}

string Parser::dest() {
    unsigned int equalSign = currentCommand.find('=');

    if (found(equalSign)) return strBefore(currentCommand, equalSign);

    return "";
}

string Parser::comp() {
    unsigned int equalSign = currentCommand.find('=');
    unsigned int semicolon = currentCommand.find(';');

    bool hasEqualSign = found(equalSign);
    bool hasSemiColon = found(semicolon);

    // 3 cases for comp
    // dest = comp ; jump
    if (hasEqualSign) {
        // there is a jump and dest command
        if (hasSemiColon)
            return strBetween(currentCommand, equalSign, semicolon);

        // there is no jump command
        return strAfter(currentCommand, equalSign);
    }

    // there is no dest command
    if (hasSemiColon) return strBefore(currentCommand, semicolon);

    return "";
}

string Parser::jump() {
    unsigned int semicolon = currentCommand.find(';');
    if (found(semicolon)) return strAfter(currentCommand, semicolon);

    return "";
}

string Parser::getCommand() { return currentCommand; }