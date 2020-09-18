#ifndef _PARSER_H_
#define _PARSER_H_

#include <fstream>
#include <string>

using command = enum { A_COMMAND = 0, C_COMMAND, L_COMMAND };

enum { VAR_START = 0x0400 };

class Parser {
   public:
    Parser(std::ifstream* in);
    bool hasMoreCommands();
    void advance();
    command commandType();
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump();
    std::string getCommand();

    //    private:
    std::ifstream* ins;
    std::string currentCommand;
    uint16_t insCount;
    uint16_t varCount;
};

#endif