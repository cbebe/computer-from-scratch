#include "Code.h"

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<std::string, std::uint8_t> compTable{
    {"0", 0x2A},   {"1", 0x3F},   {"-1", 0x3A},  {"D", 0x0C},   {"A", 0x30},
    {"!D", 0x0D},  {"!A", 0x31},  {"-D", 0x0F},  {"-A", 0x33},  {"D+1", 0x1F},
    {"A+1", 0x37}, {"D-1", 0x0E}, {"A-1", 0x32}, {"D+A", 0x02}, {"D-A", 0x13},
    {"A-D", 0x07}, {"D&A", 0x00}, {"D|A", 0x15}, {"M", 0x70},   {"!M", 0x71},
    {"-M", 0x73},  {"M+1", 0x37}, {"M-1", 0x72}, {"D+M", 0x42}, {"D-M", 0x53},
    {"M-D", 0x47}, {"D&M", 0x40}, {"D|M", 0x55}};

std::uint8_t Code::dest(std::string token, unsigned long& lineNo) {
    std::uint8_t dest_code = 0;
    for (char c : token) {
        if (c == 'M')
            dest_code |= 1 << 0;
        else if (c == 'D')
            dest_code |= 1 << 1;
        else if (c == 'A')
            dest_code |= 1 << 2;
        else {
            std::cout << "Invalid destination syntax at line " << lineNo
                      << "\n";
            exit(1);
        }
    }
    return dest_code;
}

std::uint8_t Code::comp(std::string token, unsigned long& lineNo) {
    if (compTable.find(token) != compTable.end()) return compTable[token];

    std::cout << "Invalid computation syntax at line " << lineNo << "\n";
    exit(1);
}

std::uint8_t Code::jump(std::string token, unsigned long& lineNo) {
    const std::vector<std::string> mnemonics = {"JGT", "JEQ", "JGE", "JLT",
                                                "JNE", "JLE", "JMP"};
    for (int i = 1; i < 8; ++i)
        if (!token.compare(mnemonics[i - 1])) return i;

    std::cout << "Invalid jump syntax at line " << lineNo << "\n";
    exit(1);
}
