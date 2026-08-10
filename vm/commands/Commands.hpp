#include "vm/hardware/processor/Processor.hpp"
#include <iostream>

class Command {
public:
    virtual void execute(Processor &processor) = 0;
    virtual ~Command() = default;
};

class MOV : public Command {
public:
    int reg1;
    int val1;

    MOV(int reg1, int val1) : reg1(reg1), val1(val1) {}

    void execute(Processor& processor) override {
        processor.setRegister(reg1, val1);
    }
};

class ADD : public Command {
public:
    int reg1, reg2, reg3;

    ADD(int reg1, int reg2, int reg3) : reg1(reg1), reg2(reg2), reg3(reg3) {}

    void execute(Processor& processor) override {
        int result = processor.readRegister(reg2) + processor.readRegister(reg3);
        processor.setRegister(reg1, result);
    }
};

class PRINT : public Command {
public:
    int reg1;

    PRINT(int reg1) : reg1(reg1) {}

    void execute(Processor& processor) override {
        std::cout << processor.readRegister(reg1) << std::endl;
    }
};

class CMP : public Command {
public:
    int reg1, reg2;

    CMP(int reg1, int reg2) : reg1(reg1), reg2(reg2) {}

    void execute(Processor& processor) override {
        processor.setZeroFlag(processor.readRegister(reg1) - processor.readRegister(reg2) == 0);
    }
};

class JMP : public Command {
public:
    int ptr1;

    JMP(int ptr1) : ptr1(ptr1) {}

    void execute(Processor& processor) override {
        processor.setInstructionPointer(ptr1);
    }
};

class JZ : public JMP {
public:
    using JMP::JMP;
    void execute(Processor& processor) override {
        if (processor.readZeroFlag()) {
            processor.setInstructionPointer(ptr1);
        }
    }
};

class JNZ : public JMP {
public:
    using JMP::JMP;
    void execute(Processor& processor) override {
        if (!processor.readZeroFlag()) {
            processor.setInstructionPointer(ptr1);
        }
    }
};