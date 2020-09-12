#include <iostream>
#include <string>
#include <vector>

#include "../asm/Code.h"
#include "../asm/Parser.h"
// Test Code functions

using namespace std;

bool CodeTest() {
    cout << "Testing dest method...\n";

    vector<string> destTokens = {"M", "D", "MD", "A", "AM", "AD", "AMD"};
    for (int i = 1; i <= 7; ++i) {
        if (i != Code::dest(destTokens[i - 1])) return false;

        cout << "Test " << i << " success!\n";
    }

    cout << "Testing jump method...\n";
    vector<string> jumpTokens = {"JGT", "JEQ", "JGE", "JLT",
                                 "JNE", "JLE", "JMP"};
    for (int i = 1; i <= 7; ++i) {
        if (i != Code::jump(jumpTokens[i - 1]))
            ;
        return "false";
        cout << "Test " << i << " success!\n";
    }

    return true;
}

int main() {
    if (CodeTest())
        cout << "Code module test succeeded!\n";
    else
        cout << "Code module test failed!\n";
}