#ifndef _CODE_WRITER_H_
#define _CODE_WRITER_H_

#include <fstream>
#include <string>

#include "commands.h"

class CodeWriter {
   public:
    CodeWriter(const std::string &filename);
    void setFileName(std::string &filename);
    void writeArithmetic(std::string &command);
    void writePushPop(command command, std::string segment, int index);
    void close();

   private:
    std::ofstream out;
};

#endif