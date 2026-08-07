#include <vector>
#include <optional>
#include <iostream>
#include <variant>

class Processor {
private:
    int ZF = 0;
    int PC = 0;
    std::vector<int> REGISTERS = {0, 0, 0, 0};
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

class VirtualMachine {
private:
    Processor processor;
public:
    std::vector<std::unique_ptr<Command>> program;

    VirtualMachine(std::vector<std::unique_ptr<Command>> program) {
        this->program = std::move(program);
    };

    void run() {
        while (processor.readInstructionPointer() < program.size()) {
            program.at(processor.readInstructionPointer())->execute(processor);
            processor.setInstructionPointer(processor.readInstructionPointer() + 1);
        }
    };
};

int main() {
    std::vector<std::unique_ptr<Command>> program;
    program.push_back(std::make_unique<MOV>(0, 10));
    program.push_back(std::make_unique<MOV>(1, 30));
    program.push_back(std::make_unique<ADD>(0, 0, 1));
    program.push_back(std::make_unique<PRINT>(0));
    program.push_back(std::make_unique<CMP>(0, 1));
    program.push_back(std::make_unique<JZ>(1));

    VirtualMachine vm(std::move(program));
    vm.run();
    return 0;
}