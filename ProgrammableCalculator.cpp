#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

void printRegisters(double* registers) {
    cout << "w = " << registers[0] << " x = " << registers[1] << " y = " << registers[2] << " z = " << registers[3] << endl;
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

int main(int argc, char** args) {
    /*
    1. id = id op id.
    2. id = id op constant.
    3. id = constant.
    4. id ?  go int.
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
        if (cmd.find("i") > -1) {
            // Read instructions from file
            string inFileName = cmd.substr(2);
            ifstream infile (inFileName);
            string line;
            if (infile.is_open()) {
                while (getline(infile, line)) {
                    instructions.push_back(line);
                }
                infile.close();
            }
            else {
                cout << "Unable to open file " << inFileName << endl;
            }
        }
        // Debug
        else if (cmd.compare("d") == 0) {

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
            for (auto i: instructions) {
                cout << i << endl;
                /*
                auto id1 = i.at(0);
                cout << "id1: " << id1 << endl;
                */
            }
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