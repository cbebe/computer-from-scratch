#include "Code.h"

#include <cstdint>
#include <string>
#include <vector>

std::uint8_t Code::dest(std::string token) {
    std::uint8_t dest_code = 0;
    for (char c : token) {
        if (c == 'M')
            dest_code |= 1 << 0;
        else if (c == 'D')
            dest_code |= 1 << 1;
        else if (c == 'A')
            dest_code |= 1 << 2;
    }
    return dest_code;
}

std::uint8_t Code::comp(std::string token) {
    uint8_t comp_code = 0;
    return comp_code;
}

std::uint8_t Code::jump(std::string token) {
    const std::vector<std::string> mnemonics = {"JGT", "JEQ", "JGE", "JLT",
                                                "JNE", "JLE", "JMP"};
    for (int i = 1; i < 8; ++i)
        if (!token.compare(mnemonics[i - 1])) return i;

    // never gets here
    return UINT8_MAX;
}
