#ifndef ASSEMBLER_CPP_
#define ASSEMBLER_CPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "assembler.hpp"

using namespace std;

Assembler::Assembler(Memory* _memory)
{
    memory = _memory;
};

Assembler::~Assembler()
{
};

void Assembler::assemble(const string& code)
{
    stringstream instructionStream(code);
    string op;
    int address;

    // Read instruction and address
    instructionStream >> op >> address;

    if (!isValidAssembly(op))
    {
        throw runtime_error("Unknown instruction: " + op);
    }

    // Convert to machine code
    int machine_code = 0;
    if(op == "DATA")
    {
        int data;
        instructionStream >> data;
        memory->write(address, data);
    }
    else
    {
        machine_code = (INSTRUCTION_SET[op] << 28 ) + address;
        memory->write(machine_code);
    }
    return;
};

//Need to make this more robuts. maybe exception handling or more features
bool Assembler::isValidAssembly(const string& opcode)
{
    return !(INSTRUCTION_SET.find(opcode) == INSTRUCTION_SET.end());
};

string Assembler::removeComments(const string& code)
{
    size_t commentPos = code.find(';');
    if (commentPos != string::npos) {
        return code.substr(0, commentPos);
    }

    return code; 
};

#endif // ASSEMBLER_CPP_