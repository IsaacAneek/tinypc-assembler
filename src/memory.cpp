#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "memory.hpp"
using namespace std;

void Memory::write(int data)
{
    memory.push_back(data);
}

void Memory::write(int address, int data)
{
    if (address >= memory.size())
    {
        memory.resize(address + 1, 0);
    }

    memory[address] = data;
}

int Memory::read(int address)
{
    if (address < memory.size())
    {
        return memory[address];
    }
    else
    {
        throw out_of_range("Out of range");
    }
}

void Memory::writeMemoryToFile(const string &filePath)
{
    int columns = 8;
    ofstream outputHexFile;
    outputHexFile.open(filePath);
    outputHexFile << "v2.0 raw\n";

    for (auto hexCode : memory)
    {
        stringstream hexStream;
        hexStream << hex << hexCode;
        outputHexFile << hexStream.str();

        columns--;
        if (columns <= 0)
        {
            outputHexFile << "\n";
            columns = 8;
        }
        else
        {
            outputHexFile << " ";
        }
    }
}