#include <vector>
#include "vm/commands/Commands.hpp"

class Parser {
public:
    std::vector<std::unique_ptr<Command>> parseCommandsList() {
        std::ifstream file ("main.asm");
        
        if (!file.is_open()) {
            std:cerr << "Cannot open .asm program";
            return {};
        }

        std::string line;
        std::size_t lineNumber = 0;
        while (std::getline(file, line)) {
            ++lineNumber;
            
        }
    }

    std::unique_ptr<Command> parseCommand (std::string line) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream input(line);
        std::string opcode;

        if (!(input >> opcode)) {
            std::cerr << "Empty string\n";
            return 
        }

        if (opcode == "MOV") {
            std::string destination;
            int value;

            if (!(input >> destination >> value)) {
                std::cerr << "Syntax Error: MOV R0, R1\n";
            }
        }
    }
}