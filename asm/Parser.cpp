#include "Parser.h"

using std::string;

Parser::Parser(const string &filename) { in.open(filename, std::ios::in); }

Parser::~Parser() { in.close(); }

bool Parser::hasMoreCommands() { return !in.eof(); }

void Parser::advance()
{
    string currentLine;
    do
    {
        std::getline(in, currentLine);
    } while (currentLine.compare("\n"));
}

command Parser::commandType()
{
    return A_COMMAND;
}

string Parser::symbol()
{
    return "";
}

string Parser::dest()
{
    return "";
}

string Parser::comp()
{
    return "";
}

string Parser::jump()
{
    return "";
}