#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "../asm/Code.h"
#include "../asm/Parser.h"
#include "../asm/trim.h"
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
        if (i != Code::jump(jumpTokens[i - 1])) return false;
        cout << "Test " << i << " success!\n";
    }

    return true;
}

bool ParseTest() {
    cout << "Testing string splitting...\n";

    vector<string> commands = {"M=1;JGT", "D=A+1; JLT", "A=M;JEQ "};
    vector<string> jumps = {"JGT", "JLT", "JEQ"};

    assert(commands.size() == jumps.size());

    for (unsigned int i = 0; i < commands.size(); ++i) {
        string output = trimWhitespace(stringToken(commands[i], ";"));
        string expected = jumps[i];
        if (output.compare(expected)) {
            cout << "Output:" << output << " Expected: " << expected << "\n";
            return false;
        }
        cout << "Test " << i + 1 << " success!\n";
    }

    return true;
}

int main() {
    cout << "--------------------------\nTesting Parser "
            "Modules...\n--------------------------\n";
    if (CodeTest())
        cout << "Code module test succeeded!\n";
    else
        cout << "Code module test failed!\n";

    if (ParseTest())
        cout << "Code module test succeeded!\n";
    else
        cout << "Code module test failed!\n";
}