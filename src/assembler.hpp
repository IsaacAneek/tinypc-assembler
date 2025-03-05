
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "memory.hpp"

using namespace std;

class Assembler
{
    private:
    unordered_map<string, int> INSTRUCTION_SET =
    {
        {"AND", 0x00},  {"ADD", 0x01},
        {"STO", 0x02},  {"ISZ", 0x03},
        {"BSB", 0x04},  {"BUN", 0x05},
        {"LDA", 0x06},  {"HLT", 0x07},
        {"NOP", 0x08},  {"ADD", 0x09},
        {"DATA", 0x0A}
    };
    Memory* memory;

    public:
    Assembler(Memory* _memory);
    ~Assembler();
    void assemble(const string& code);
    bool isValidAssembly(const string& code);
    string removeComments(const string& code);
};