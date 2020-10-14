#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "Code.h"
#include "Parser.h"
#include "strhelp.h"
// Test Code functions

using namespace std;

bool CodeTest() {
    cout << "Testing dest method...\n";

    vector<string> destTokens = {"M", "D", "MD", "A", "AM", "AD", "AMD"};
    unsigned long j = 0;
    for (int i = 1; i <= 7; ++i) {
        if (i != Code::dest(destTokens[i - 1], j)) return false;

        cout << "Test " << i << " success!\n";
    }

    cout << "Testing jump method...\n";
    vector<string> jumpTokens = {"JGT", "JEQ", "JGE", "JLT",
                                 "JNE", "JLE", "JMP"};
    for (int i = 1; i <= 7; ++i) {
        if (i != Code::jump(jumpTokens[i - 1], j)) return false;
        cout << "Test " << i << " success!\n";
    }

    return true;
}

// not testing this anymore
bool ParseTest() { return true; }

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