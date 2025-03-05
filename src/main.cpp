#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "assembler.hpp"
#include "memory.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        cerr << "Usage main <filename>.tpasm\n";
        return 0;
    }

    string filePath = argv[1];
    string instructions;
    string extension = ".tpasm";
    ifstream readTpasmFile;
    Memory memory;
    Assembler assembler(&memory);


    if(filePath.find(extension) == string::npos)
    {
        cerr << "Invalid file extension.\n";
        return 0;
    }

    auto pos = filePath.find('.');
    string outputFileName = filePath.substr(0, pos);

    try
    {
        readTpasmFile.open(filePath);

        while(getline(readTpasmFile, instructions))
        {
            assembler.assemble(instructions);
        }

        memory.writeMemoryToFile(outputFileName);
    }
    catch(exception e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
