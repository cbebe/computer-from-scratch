#ifndef _VM_PARSER_H_
#define _VM_PARSER_H_

#include <fstream>
#include <string>

#include "Parser.h"
#include "vm_commands.h"

class VMParser : public Parser {
   public:
    VMParser(const std::string &filename) : Parser(filename) {}
    command commandType();
    std::string arg1();
    std::string arg2();
};

#endif