#ifndef MEMORY_HPP_
#define MEMORY_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

class Memory
{
    private:
    int PC = 0;
    vector<int> memory;
    int columns = 8;

    public:
    void write(int data);
    void write(int address, int data);
    int read(int address);
    void writeMemoryToFile(const string& filePath);

};

#endif // MEMORY_HPP_