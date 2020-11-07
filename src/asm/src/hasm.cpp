/**
 * HASM - Hack ASseMbler
 * Created by Charles Ancheta
 */

#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

#include "ASMParser.h"
#include "Code.h"
#include "SymbolTable.h"
#include "strhelp.h"

void die(std::string message) {
    std::cout << message;
    exit(1);
}

SymbolTable parseSymbols(std::string &inputFilename) {
    ASMParser source(inputFilename);
    SymbolTable table;
    unsigned long lineNo = 0;
    unsigned long romNum = 0;

    while (true) {
        source.advance(lineNo);
        if (!source.hasMoreCommands()) return table;

        command type = source.commandType(lineNo);
        if (type == A_COM || type == C_COM) romNum++;

        std::string symbol = source.symbol();
        if (type == L_COM && !table.contains(symbol))
            table.addEntry(symbol, romNum);
    }
}

void assembleCode(std::string &inputFilename, std::ofstream &out,
                  SymbolTable &table) {
    ASMParser source(inputFilename);
    unsigned long lineNo = 0;
    unsigned long address = 0x10;  // 0x0 to 0xF are predefined

    while (true) {
        source.advance(lineNo);
        if (!source.hasMoreCommands()) {
            uint16_t halt = 0x0010;  // 0x1000 in big endian
            out.write(reinterpret_cast<const char *>(&halt), sizeof halt);
            break;
        }

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
            instruction = (7 << 13) | (Code::comp(source.comp(), lineNo) << 6) |
                          (Code::dest(source.dest(), lineNo) << 3) |
                          Code::jump(source.jump(), lineNo);
        }
        // write in big endian format
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
    SymbolTable table = parseSymbols(inFilename);
    // Assemble machine code
    assembleCode(inFilename, fout, table);

    fout.close();
}