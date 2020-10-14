#ifndef _ASM_PARSER_H_
#define _ASM_PARSER_H_

#include <fstream>
#include <string>

#include "../../Parser.h"

using command = enum commandtype { A_COM = 0, C_COM, L_COM };

enum { VAR_START = 0x0400 };

class ASMParser : public Parser {
   public:
    ASMParser(const std::string& filename) : Parser(filename) {}
    command commandType(unsigned long& lineNo);
    std::string symbol();
    std::string dest();
    std::string comp();
    std::string jump();
    std::string getCommand();

   private:
    unsigned long insCount = 0;
    unsigned long varCount = 0;
};

#endif