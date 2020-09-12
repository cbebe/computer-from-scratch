#ifndef _CODE_H_
#define _CODE_H_

#include <cstdint>
#include <string>
#include <vector>

class Code {
   public:
    static std::uint8_t dest(std::string dest);
    static std::uint8_t comp(std::string comp);
    static std::uint8_t jump(std::string jump);
};

#endif