#include <vector>
#include <optional>
#include <iostream>
#include <variant>

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