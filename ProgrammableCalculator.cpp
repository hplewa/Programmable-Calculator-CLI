#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char** args) {
    double w, x, y, z = 0.0;
    string inFileName = "instructions.txt";
    string line;
    ifstream infile (inFileName);
    if (infile.is_open()) {
        while (getline(infile, line)) {
            cout << line << endl;
        }
        infile.close();
    }
    else {
        cout << "Unable to open file " << inFileName << endl;
    }
}