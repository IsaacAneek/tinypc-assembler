#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, int> INSTRUCTION_SET =
{
    {"AND", 0x00},
    {"ADD", 0x01},
    {"STO", 0x02},
    {"ISZ", 0x03},
    {"BSB", 0x04},
    {"BUN", 0x05},
    {"LDA", 0x06},
    {"HLT", 0x07},
    {"NOP", 0x08},
    {"ADD", 0x09},
    {"DATA", 0x0A}
};
int PC = 0;
vector<int> memory(10);

void assemble(const string &instruction)
{
    stringstream instructionStream(instruction);
    string op;
    int address;

    // Read instruction and address
    instructionStream >> op >> address;

    if (INSTRUCTION_SET.find(op) == INSTRUCTION_SET.end())
    {
        throw runtime_error("Unknown instruction: " + op);
    }

    // Convert to machine code
    int machine_code = 0;
    if(op == "DATA")
    {
        int data;
        instructionStream >> data;
        memory.resize(address + 1);
        memory[address] = data;
    }
    else
    {
        machine_code = (INSTRUCTION_SET[op] << 28 ) + address;
        memory.push_back(machine_code);
    }
    return;

    // Convert to uppercase hex string
//    stringstream hexStream;
//    hexStream << hex << machine_code;
//    return hexStream.str();
}

void writeMemoryToFile(string& filePath, vector<int>& memory)
{
    int columns = 8;
    ofstream outputHexFile;
    outputHexFile.open(filePath);
    outputHexFile << "v2.0 raw\n";

    for(auto hexCode : memory)
    {
        stringstream hexStream;
        hexStream << hex << hexCode;
        outputHexFile << hexStream.str();

        columns--;
        if(columns <= 0)
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

int main(int argc, char* argv[])
{
    string filePath = argv[1];
    string instructions;
    string extension = ".tpasm";
    ifstream readTpasmFile;


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
            assemble(instructions);
        }

        writeMemoryToFile(outputFileName, memory);
    }
    catch(exception e)
    {
        cerr << e.what() << endl;
    }

    return 0;
}
