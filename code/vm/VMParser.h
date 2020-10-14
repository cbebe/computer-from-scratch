#ifndef _VM_PARSER_H_

#define _VM_PARSER_H_

#include <fstream>
#include <string>

#include "Parser.h"
#include "commands.h"

class VMParser : public Parser {
   public:
    command commandType();
    std::string arg1();
    std::string arg2();
};

#endif