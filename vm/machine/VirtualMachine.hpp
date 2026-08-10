#include <vector>
#include "vm/hardware/processor/Processor.hpp"
#include "vm/commands/Commands.hpp"

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