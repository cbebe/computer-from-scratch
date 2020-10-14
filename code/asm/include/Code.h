#ifndef _CODE_H_
#define _CODE_H_

#include <cstdint>
#include <string>
#include <vector>

class Code {
   public:
    static std::uint8_t dest(std::string dest, unsigned long& lineNo);
    static std::uint8_t comp(std::string comp, unsigned long& lineNo);
    static std::uint8_t jump(std::string jump, unsigned long& lineNo);
};

#endif