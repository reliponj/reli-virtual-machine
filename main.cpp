#include <vector>
#include <optional>
#include <iostream>
#include <variant>

class Processor {
private:
    int ZF = 0;
    std::vector<int> REGISTERS = {0, 0, 0, 0};
public:
    void setRegister(int address, int value) {
        REGISTERS[address] = value;
    }

    int readRegister(int address) {
        return REGISTERS[address];
    }

    void setZeroFlag(bool value) {
        ZF = value ? 1 : 0;
    }

    int readZeroFlag() {
        return ZF;
    }
};

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

    void execute(Processor& processor) {
        processor.setRegister(reg1, val1);
    }
};

class ADD : public Command {
public:
    int reg1, reg2, reg3;

    ADD(int reg1, int reg2, int reg3) : reg1(reg1), reg2(reg2), reg3(reg3) {}

    void execute(Processor& processor) {
        int result = processor.readRegister(reg2) + processor.readRegister(reg3);
        processor.setRegister(reg1, result);
    }
};

class PRINT : public Command {
public:
    int reg1;

    PRINT(int reg1) : reg1(reg1) {}

    void execute(Processor& processor) {
        std::cout << processor.readRegister(reg1) << std::endl;
    }
};

class CMP : public Command {
public:
    int reg1, reg2;

    CMP(int reg1, int reg2) : reg1(reg1), reg2(reg2) {}

    void execute(Processor& processor) {
        processor.setZeroFlag(processor.readRegister(reg1) - processor.readRegister(reg2) == 0);
    }
};

class VirtualMachine {
private:
    Processor processor;
public:
    std::vector<Command> program;

    VirtualMachine(std::vector<Command> program) {
        this->program = program;
    };

    void run() {
        for (int i = 0; i < this->program.size(); i++) {
            program[i].execute(processor);
        }
    };
};

int main() {
    std::vector<Command> program = {
        MOV(0, 10),
        MOV(1, 30),
        ADD(0, 0, 1),
        PRINT(0),
    };
    VirtualMachine vm = VirtualMachine(program);
    vm.run();
    return 0;
}