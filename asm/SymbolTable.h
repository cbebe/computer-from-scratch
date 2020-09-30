#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include <string>
#include <unordered_map>

class SymbolTable {
   public:
    SymbolTable();
    void addEntry(std::string symbol, unsigned int address);

    bool contains(std::string symbol);

    unsigned int getAddress(std::string symbol);

   private:
    std::unordered_map<std::string, unsigned int> addressTable;
};

#endif