#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

void printRegisters(double* registers) {
    cout << "w = " << registers[0] 
        << " x = " << registers[1] 
        << " y = " << registers[2] 
        << " z = " << registers[3] 
        << endl;
}

void printMenu() {
    cout << "Type:" << endl 
    << "i file_name - Input file - read instructions from this file" << endl
    << "d - Debug - execute next instruction, print debugging info" << endl 
    << "r - Run - execute instruction from current index" << endl
    << "p - Print - print instructions" << endl
    << "h - help" << endl 
    << "q - quit" << endl;
}

void printInstructions(vector<string> instructions) {
    int i = 1;
    for (auto instruction: instructions) {
        cout << i++ << ": " << instruction << endl;
        /*
        auto id1 = i.at(0);
        cout << "id1: " << id1 << endl;
        */
    }
}

vector<string> readInstructions(string cmd) {
    // Read instructions from file
    vector<string> instructions = vector<string>();
    string inFileName = cmd.substr(2);
    ifstream infile (inFileName);
    string line;
    if (infile.is_open()) {
        while (getline(infile, line)) {
            // Remove . at the end of instruction
            line.erase(line.find("."));
            instructions.push_back(line);
        }
        infile.close();
        cout << "Successfully read " << inFileName << endl;
    }
    else {  
        cout << "Unable to open file " << inFileName << endl;
    }
    return instructions;
}

// 1. id = id op id.
void executeType1(vector<string> instructions, int index, double* registers) {
    // Parse instruction
    string instruction = instructions[index];
    int id1 = instruction[0] - 'w';
    int id2 = instruction[4] - 'w';
    int id3 = instruction[instruction.length() - 1] - 'w';
    string op = instruction.substr(6, 1);
    // Determine operand
    if (instruction.substr(6, 2).compare("**") == 0) {
        registers[id1] = pow(registers[id2], registers[id3]);
    }
    else if (op.compare("+") == 0) {
        registers[id1] = registers[id2] + registers[id3];

    }
    else if (op.compare("-") == 0) {
        registers[id1] = registers[id2] - registers[id3];

    }
    else if (op.compare("*") == 0) {
        registers[id1] = registers[id2] * registers[id3];

    }
    else if (op.compare("/") == 0) {
        registers[id1] = registers[id2] / registers[id3];
    }
}

// 2. id = id op constant.
void executeType2(vector<string> instructions, int index, double* registers) {
    // Parse instruction
    string instruction = instructions[index];
    int id1 = instruction[0] - 'w';
    int id2 = instruction[4] - 'w';
    double constant = stof(instruction.substr(8));
    string op = instruction.substr(6, 1);
    // Determine operand
    if (instruction.substr(6,2).compare("**") == 0) {
        registers[id1] = pow(registers[id2], constant);
    }
    else if (op.compare("+") == 0) {
        registers[id1] = registers[id2] + constant;
    }
    else if (op.compare("-") == 0) {
        registers[id1] = registers[id2] - constant;

    }
    else if (op.compare("*") == 0) {
        registers[id1] = registers[id2] * constant;

    }
    else if (op.compare("/") == 0) {
        registers[id1] = registers[id2] / constant;
    }
}

// 3. id = constant.
void executeType3(vector<string> instructions, int index, double* registers) {
    // Parse instruction
    string instruction = instructions[index];
    int id1 = instruction[0] - 'w';
    double constant = stof(instruction.substr(4));
    // Executing
    registers[id1] = constant;
}

//void executeInstruction(vector<string>, int, double*);

// 4. id ? go int.
void executeType4(vector<string> instructions, int& index, double* registers) {
    string instruction = instructions[index];
    int id1 = instruction[0] - 'w';
    // Offset index by 1
    int lineNumber = stoi(instruction.substr(7)) - 2;
    // If value of register left of ? is not 0, execute the line provided right of go
    if (registers[id1] != 0) {
        index = lineNumber;
        // executeInstruction(instructions, lineNumber, registers);
    }
}

// Execute the instruction in instructions at the index, on the registers
void executeInstruction(vector<string> instructions, int& index, double* registers) {
    if (index >= instructions.size()) {
        cout << "Index: " << index << " exceeds the number of instructions: " << instructions.size() << endl;
        return;
    }
    string instruction = instructions[index];
    string op1;
    // Determine type of instruction
    op1 = instruction.at(2);
    // Type 4. id ? go int
    if (op1.compare("?") == 0) {
        executeType4(instructions, index, registers);
    }
    // Type 3. id = constant
    else if (!isalpha(instruction.at(4))) {
        // The character after op1 is not alphabetic -> it's a constant
        executeType3(instructions, index, registers);
    }
    // Type 2 id = id op constant
    else if (!isalpha(instruction.at(instruction.length() - 1))) {
        // Last character is not alphabetic -> it's a constant
        executeType2(instructions, index, registers);
    }
    // Type 1 id = id op id
    else{
        executeType1(instructions, index, registers);
    }
    index++;
}

int main(int argc, char** args) {
    /*
    1. id = id op id.
    2. id = id op constant.
    3. id = constant.
    4. id ? go int.
    */
    // Instructions read from file
    auto instructions = vector<string>();
    // Registers for      w, x, y, z
    double registers[] = {0, 0, 0, 0};

    // Ask user how to execute instructions
    string cmd = "";
    printMenu();
    
    // Initialize instructions
    while (cmd.find("i") != 0) {
        getline(cin, cmd);
        // Input
        if (cmd.find("i") == 0) {
            // Read instructions from file
            instructions = readInstructions(cmd);
        }
        else {
            cout << "Please enter: i file_name : to read in instructions." << endl;
        }
    }

    // Limit of 100 instructions per program execution
    int index = 0;
    int evaluationLimit = 100;
    int evaluations = 0;
    while (1) {
        getline(cin, cmd);
        // Debug
        if (cmd.compare("d") == 0) {
            // Get index
            if (index < instructions.size()) {
                cout << "Instruction to be executed: " << index + 1 << ". " << instructions[index] << endl;
                cout << "Registers before: ";
                printRegisters(registers);
                executeInstruction(instructions, index, registers);
                cout << "Registers after: ";
                printRegisters(registers);
            }
            else {
                cout << "Index: " << index << " doesn't have an instruction." << endl;
            }
        }
        // Run
        else if (cmd.compare("r") == 0) {
            while (evaluations < evaluationLimit) {
                if (index < instructions.size()) {
                    executeInstruction(instructions, index, registers);
                    evaluations++;
                }
            }
            cout << evaluations << " evaluations have been made, reaching the limit of " << evaluationLimit << "." << endl;
            cout << "Press c to increase the evaluation limit by 100." << endl;
        }
        // Print instructions and registers
        else if (cmd.compare("p") == 0) {
            printInstructions(instructions);
            printRegisters(registers);
            cout << "Evaluations: " << evaluations << endl;
            if (index < instructions.size()) {
                cout << "Instruction to be executed: " << index + 1 << ". " << instructions[index] << endl;
            }
            else {
                cout << "Current index: " << index + 1 << "does not have an associated instruction." << endl;
            }
        }
        // Continue executing by increasing limit        
        else if (cmd.compare("c") == 0) {
            cout << "Increasing the limit of how many evaluations can be made by 100." << endl;
            evaluationLimit += 100;
        }
        // Help
        else if (cmd.compare("h") == 0) {
            printMenu();
        }
        // Quit
        else if(cmd.compare("q") == 0) {
            cout << "Quitting..." << endl;
            break;
        }
    }
}