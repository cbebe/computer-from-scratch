#ifndef _PARSER_H_
#define _PARSER_H_

#include <fstream>
#include <string>

using command = enum { A_COMMAND = 0, C_COMMAND, L_COMMAND };

enum { VAR_START = 0x0400 };

class Parser {
   public:
    Parser(const std::string &filename);
    bool hasMoreCommands();
    void advance(unsigned long &lineNo);
    command commandType(unsigned long &lineNo);
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump();
    std::string getCommand();

   private:
    std::ifstream in;
    std::string currentCommand;
    unsigned long insCount = 0;
    unsigned long varCount = 0;
};

#endif