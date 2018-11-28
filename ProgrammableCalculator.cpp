#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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
    << "c - Continue - execute remaining instructions" << endl
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
    for (int i = 0 ; i < 100; i++) {
        getline(cin, cmd);
        // Input
        if (cmd.find("i") == 0) {
            // Read instructions from file
            instructions = readInstructions(cmd);
        }
        // Debug
        else if (cmd.compare("d") == 0) {
            // Pop off the front
            auto instruction = instructions.front();
            instructions.erase(instructions.begin());
            string id1, op1, id2, op2, id3;
            // Parse instruction
            id1 = instruction.at(0);
            op1 = instruction.at(2);
        }
        // Run
        else if (cmd.compare("r") == 0) {

        }
        // Continue
        else if (cmd.compare("c") == 0) {
            // Execute all instructions
        }
        // Print
        else if (cmd.compare("p") == 0) {
            // Print instructions
            printInstructions(instructions);
        }
        // Help
        else if (cmd.compare("h") == 0) {
            printMenu();
        }
        // Quit
        else if(cmd.compare("q") == 0) {
            break;
        }

    }
}