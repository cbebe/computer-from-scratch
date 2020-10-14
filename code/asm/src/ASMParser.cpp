#include "ASMParser.h"

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

command ASMParser::commandType(unsigned long &lineNo) {
    string command = getCommand();
    if (commandTable.find(command[0]) != commandTable.end())
        return commandTable[command[0]];

    std::cout << "Invalid syntax at line " << lineNo << "\n";
    exit(1);
}

string ASMParser::symbol() {
    string command = getCommand();
    if (command[0] == '@') return strAfter(command, 0);

    size_t openParens = command.find('(');
    size_t closedParens = command.find(')');

    if (found(openParens) && found(closedParens))
        return strBetween(command, openParens, closedParens);

    return "";
}

string ASMParser::dest() {
    size_t equalSign = getCommand().find('=');

    if (found(equalSign)) return strBefore(getCommand(), equalSign);

    return "";
}

string ASMParser::comp() {
    string command = getCommand();
    size_t equalSign = command.find('=');
    size_t semicolon = command.find(';');

    bool hasEqualSign = found(equalSign);
    bool hasSemiColon = found(semicolon);

    // 3 cases for comp
    // dest = comp ; jump
    if (hasEqualSign) {
        // there is a jump and dest command
        if (hasSemiColon) return strBetween(command, equalSign, semicolon);
        // there is no jump command
        return strAfter(command, equalSign);
    }

    // there is no dest command
    if (hasSemiColon) return strBefore(command, semicolon);

    return "";
}

string ASMParser::jump() {
    size_t semicolon = getCommand().find(';');
    if (found(semicolon)) return strAfter(getCommand(), semicolon);

    return "";
}
