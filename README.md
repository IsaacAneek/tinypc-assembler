# tinypc-assembler
A tiny assembler written for a tiny PC.
It converts tiny-pc assembly instructions into logisim compatible RAM image.
The assembler converts the instructions into correspoding hex code. The instruction bits are 32 bits. The first 4 bits represent opcode and the last 5 bits represent memory address. In case of "DATA" instruction the whole 32 bit value represents an integer data.
# Usage
`assembler.exe <filenamle>.tpasm`
