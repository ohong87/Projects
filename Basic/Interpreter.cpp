// Interpreter.cpp
#include "AddStatement.h"
#include "DivStatement.h"
#include "EndStatement.h"
#include "GoSubStatement.h"
#include "GoToStatement.h"
#include "IfStatement.h"
#include "LetStatement.h"
#include "MultStatement.h"
#include "PrintAllStatement.h"
#include "PrintStatement.h"
#include "ProgramState.h"
#include "ReturnStatement.h"
#include "Statement.h"
#include "SubStatement.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// parseProgram() takes a filename as a parameter, opens and reads the
// contents of the file, and returns an vector of pointers to Statement.
void parseProgram(istream& inf, vector<Statement*>& program);

// parseLine() takes a line from the input file and returns a Statement
// pointer of the appropriate type.  This will be a handy method to call
// within your parseProgram() method.
Statement* parseLine(string line);

// interpretProgram() reads a program from the given input stream
// and interprets it, writing any output to the given output stream.
// Note:  you are required to implement this function!
void interpretProgram(istream& inf, ostream& outf);

int main() {
    cout << "Enter BASIC program file name: ";
    string filename;
    getline(cin, filename);
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "Cannot open " << filename << "!" << endl;
        return 1;
    }
    interpretProgram(infile, cout);

    return 0;
}

void parseProgram(istream& inf, vector<Statement*>& program) {
    program.push_back(NULL);

    string line;
    while (!inf.eof()) {
        getline(inf, line);
        program.push_back(parseLine(line));
    }
}

Statement* parseLine(string line) {
    Statement* statement;
    stringstream ss;
    string type;
    string var;
    string currentLine;
    string mathVal;
    int val;

    // Used in the if statement
    int val2;
    string cmpr;
    string then;

    ss << line;
    ss >> currentLine;
    ss >> type;

    if (type == "LET") {
        ss >> var;
        ss >> val;
        // Note:  Because the project spec states that we can assume the file
        //	  contains a syntactically legal program, we know that
        //	  any line that begins with "LET" will be followed by a space
        //	  and then a variable and then an integer value.
        statement = new LetStatement(var, val);
    } else if (type == "END" || type == ".") {
        statement = new EndStatement();
    } else if (type == "PRINT") {
        ss >> var;
        statement = new PrintStatement(var);
    } else if (type == "PRINTALL") {
        statement = new PrintAllStatement();
    } else if (type == "ADD") {
        ss >> var;
        ss >> mathVal;

        // if mathVal is an int, then this constructor is called
        if (((int)mathVal[0] >= 48 && (int)mathVal[0] <= 57) || (int)mathVal[0] == 45) {
            int temp = 0;
            temp = stoi(mathVal);
            statement = new AddStatement(var, temp);
        }
        // if mathVal is a variable, then this constructor is called
        else {
            statement = new AddStatement(var, mathVal);
        }
    } else if (type == "SUB") {
        ss >> var;
        ss >> mathVal;

        if (((int)mathVal[0] >= 48 && (int)mathVal[0] <= 57) || (int)mathVal[0] == 45) {
            int temp = 0;
            temp = stoi(mathVal);
            statement = new SubStatement(var, temp);
        } else {
            statement = new SubStatement(var, mathVal);
        }
    } else if (type == "MULT") {
        ss >> var;
        ss >> mathVal;

        if (((int)mathVal[0] >= 48 && (int)mathVal[0] <= 57) || (int)mathVal[0] == 45) {
            int temp = 0;
            temp = stoi(mathVal);
            statement = new MultStatement(var, temp);
        } else {
            statement = new MultStatement(var, mathVal);
        };
    } else if (type == "DIV") {
        ss >> var;
        ss >> mathVal;

        if (((int)mathVal[0] >= 48 && (int)mathVal[0] <= 57) || (int)mathVal[0] == 45) {
            int temp = 0;
            temp = stoi(mathVal);
            statement = new DivStatement(var, temp);
        } else {
            statement = new DivStatement(var, mathVal);
        };
    } else if (type == "GOTO") {
        ss >> val;
        statement = new GoToStatement(val);
    } else if (type == "IF") {
        ss >> var;
        ss >> cmpr;
        ss >> val;
        ss >> then;
        ss >> val2;

        statement = new IfStatement(var, cmpr, val, val2);
    } else if (type == "GOSUB") {
        ss >> val;
        statement = new GoSubStatement(val);
    } else if (type == "RETURN") {
        statement = new ReturnStatement();
    }
    return statement;
}

void interpretProgram(istream& inf, ostream& outf) {
    vector<Statement*> program;
    parseProgram(inf, program);
    ProgramState* temp = new ProgramState(program.size());

    while (!temp->getIsEnd() && !temp->getBreak()) {
        program[temp->getLineNumber()]->execute(temp, outf);
    }

    for (unsigned int i = 1; i < program.size(); i++) {
        delete program[i];
    }

    delete temp;
}
