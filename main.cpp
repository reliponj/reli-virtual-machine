#include <vector>
#include <optional>
#include <iostream>

enum class Code {
    MOV, ADD, PRINT
};

class Command {
public:
    Code code;
    int arg1;
    std::optional<int> arg2;

    Command(Code code, int arg1, std::optional<int> arg2 = std::nullopt) {
        this->code = code;
        this->arg1 = arg1;
        this->arg2 = arg2;
    }
};

class VirtualMachine {
private:
    std::vector<int> REGISTERS = {0, 0, 0, 0};
    int ADD_COMMAND_REGISTER = 0;
public:
    std::vector<Command> program;

    VirtualMachine(std::vector<Command> program) {
        this->program = program;
    };

    void run() {
        for (int i = 0; i < this->program.size(); i++) {
            process(program[i]);
        }
    };

    void process(Command command) {
        Code code = command.code;
        int arg1 = command.arg1;
        std::optional<int> arg2 = command.arg2;

        if (code == Code::MOV) {
            if (arg2.has_value())
            this->REGISTERS[arg1] = arg2.value();
        } else if (code == Code::ADD) {
            if (arg2.has_value())
            this->REGISTERS[ADD_COMMAND_REGISTER] = this->REGISTERS[arg1] + this->REGISTERS[arg2.value()];
        } else if (code == Code::PRINT) {
            std::cout << this->REGISTERS[arg1] << std::endl;
        }
    }
};

int main() {
    std::vector<Command> program = {
        Command(Code::MOV, 0, 10),
        Command(Code::MOV, 1, 30),
        Command(Code::ADD, 0, 1),
        Command(Code::PRINT, 0),
    };
    VirtualMachine vm = VirtualMachine(program);
    vm.run();
    return 0;
}