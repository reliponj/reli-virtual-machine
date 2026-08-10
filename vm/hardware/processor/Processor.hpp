#include "Registers.hpp"

class Processor {
private:
    int ZF = 0;
    int PC = 0;
    std::unordered_map<Register, int> REGISTERS{
        {Register::R0, 0},
        {Register::R1, 0},
        {Register::R2, 0},
        {Register::R3, 0},
        {Register::R4, 0},
        {Register::R5, 0},
        {Register::R6, 0},
        {Register::R7, 0},
    };
public:
    void setRegister(int address, int value) {
        REGISTERS[address] = value;
    }

    const int readRegister(int address) {
        return REGISTERS[address];
    }

    void setZeroFlag(bool value) {
        ZF = value ? 1 : 0;
    }

    const int readZeroFlag() {
        return ZF;
    }

    void setInstructionPointer(int value) {
        PC = value;
    }

    const int readInstructionPointer() {
        return PC;
    }
};