/**
 * HASM - Hack ASseMbler
 * Created by Charles Ancheta
 */

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "Code.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "strhelp.h"

void die(std::string message) {
    std::cout << message;
    exit(1);
}

void parseSymbols(std::string &inputFilename, SymbolTable &table) {
    Parser source(inputFilename);
    unsigned long lineNo = 0;
    unsigned long romNum = 0;

    while (true) {
        source.advance(lineNo);
        if (!source.hasMoreCommands()) return;

        if (source.commandType(lineNo) == A_COM ||
            source.commandType(lineNo) == C_COM)
            romNum++;

        std::string symbol = source.symbol();
        if (source.commandType(lineNo) == L_COM && !table.contains(symbol))
            table.addEntry(symbol, romNum);
    }
}

void assembleCode(std::string &inputFilename, std::ofstream &out,
                  SymbolTable &table) {
    Parser source(inputFilename);
    Code code;
    unsigned long lineNo = 0;
    unsigned long address = 0x10;  // 0x0 to 0xF are predefined

    while (true) {
        source.advance(lineNo);
        if (!source.hasMoreCommands()) return;

        std::uint16_t instruction;

        if (source.commandType(lineNo) == A_COM) {
            std::string symbol = source.symbol();
            instruction = 0;
            // convert decimal to A instruction
            if (!found(symbol.find_first_not_of("0123456789"))) {
                instruction = std::stoi(symbol);
            } else {
                if (!table.contains(symbol)) table.addEntry(symbol, address++);
                instruction = table.getAddress(symbol);
            }
        } else if (source.commandType(lineNo) == C_COM) {
            instruction = 7 << 13;  // C instruction bits
            std::string comp = source.comp();
            std::cout << comp;
            instruction |= code.comp(comp, lineNo) << 6;
            instruction |= code.dest(source.dest(), lineNo) << 3;
            instruction |= code.jump(source.jump(), lineNo);
        }
        instruction = instruction << 8 | instruction >> 8;
        out.write(reinterpret_cast<const char *>(&instruction),
                  sizeof instruction);
    }
}

int main(int argc, const char *argv[]) {
    if (argc < 2 || argc > 3)
        die("Usage: " + std::string(argv[0]) + " infile [outfile]\n");

    std::string inFilename = argv[1];
    std::string outFilename = (argc == 3) ? argv[2] : "a.out";

    std::ofstream fout(outFilename, std::ios::out | std::ios_base::binary);
    if (fout.fail()) die("Output file creation failed.\n");

    // Generate symbol table
    SymbolTable table;
    parseSymbols(inFilename, table);
    // Assemble machine code
    assembleCode(inFilename, fout, table);

    fout.close();
}