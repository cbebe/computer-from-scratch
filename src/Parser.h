#ifndef _PARSER_H_
#define _PARSER_H_

#include <fstream>
#include <string>

// Generic Parser class for both VM and ASM parser

class Parser {
   public:
    Parser(const std::string &filename);
    bool hasMoreCommands();
    void advance(unsigned long &lineNo);
    std::string getCommand();

   private:
    std::ifstream in;
    std::string currentCommand;
};

#endif