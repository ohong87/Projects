#include "ProgramState.h"

#include <iostream>

using namespace std;

// constructor
ProgramState::ProgramState(int numLines) {
    m_numLines = numLines;
    if (m_numLines > 1000) {
        isBreak = true;
    } else {
        isBreak = false;
    }
    counter = 1;
    isEnd = false;
}

void ProgramState::incrementCounter() { counter++; }

void ProgramState::letStatement(string str, int num) {
    // if str doesn't exist, then this is called
    if (var.find(str) == var.end()) {
        var.emplace(str, num);
    }
    // if str already exists, then it is updated
    else {
        map<string, int>::iterator temp;
        temp = var.find(str);

        temp->second = num;
    }
}

void ProgramState::setIsEnd() { isEnd = true; }

bool ProgramState::getIsEnd() { return isEnd; }

void ProgramState::printStatement(string str, ostream& outf) {
    map<string, int>::iterator temp;
    temp = var.find(str);

    // if str exists, print the value
    if (temp != var.end()) {
        outf << temp->second << endl;
    }
    // if str does not exist, then add it to the map and print 0
    else {
        letStatement(str, 0);
        outf << "0" << endl;
    }
}

int ProgramState::getLineNumber() { return counter; }

void ProgramState::printAllStatement(std::ostream& outf) {
    map<string, int>::iterator i;
    for (i = var.begin(); i != var.end(); i++) {
        outf << i->first << " " << i->second << endl;
    }
}

void ProgramState::addStatement(string s, int n) {
    // finds the value and adds n to it
    map<string, int>::iterator temp;
    temp = var.find(s);

    if (temp != var.end()) {
        temp->second += n;
    }
}

void ProgramState::subStatement(string s, int n) {
    // finds the value and subtracts n from it
    map<string, int>::iterator temp;
    temp = var.find(s);

    if (temp != var.end()) {
        temp->second -= n;
    }
}

void ProgramState::multStatement(string s, int n) {
    // finds the value and multiplies it by n
    map<string, int>::iterator temp;
    temp = var.find(s);

    if (temp != var.end()) {
        temp->second *= n;
    }
}

void ProgramState::divStatement(string s, int n) {
    // divide by 0 error
    if (n == 0) {
        cout << "Divide by zero exception" << endl;
        isBreak = true;
    }
    // if not zero, finds the value and divides it by n
    else {
        map<string, int>::iterator temp;
        temp = var.find(s);

        if (temp != var.end()) {
            temp->second /= n;
        }
    }
}

int ProgramState::getValue(string s) {
    // returns the value of a variable
    map<string, int>::iterator temp;
    temp = var.find(s);

    if (temp != var.end()) {
        return temp->second;
    }
    // if the variable does not exist, then return 0 and add the variable to the map
    else {
        letStatement(s, 0);
        return 0;
    }
}

void ProgramState::goToStatement(int n, std::ostream& outf) {
    // test cases
    if (n < 1) {
        outf << "Illegal jump instruction" << endl;
        isBreak = true;
    } else if (n > m_numLines) {
        outf << "Illegal jump instruction" << endl;
        isBreak = true;
    }
    // if n is a valid line number, set the line number to it
    else {
        counter = n - 1;
    }
}

void ProgramState::setBreak() { isBreak = true; }

bool ProgramState::getBreak() { return isBreak; }

void ProgramState::ifStatement(string str, string compare, int num, int num2, std::ostream& outf) {
    // tests for illegal line numbers
    if (num2 < 1) {
        outf << "Illegal jump instruction" << endl;
        isBreak = true;
    } else if (num2 > m_numLines) {
        outf << "Illegal jump instruction" << endl;
        isBreak = true;
    }
    // enters if valid line number. Tests different comparisons
    else {
        if (compare == "<") {
            if (getValue(str) < num) {
                goToStatement(num2, outf);
            }
        } else if (compare == "<=") {
            if (getValue(str) <= num) {
                goToStatement(num2, outf);
            }
        } else if (compare == ">") {
            if (getValue(str) > num) {
                goToStatement(num2, outf);
            }
        } else if (compare == ">=") {
            if (getValue(str) >= num) {
                goToStatement(num2, outf);
            }
        } else if (compare == "=") {
            if (getValue(str) == num) {
                goToStatement(num2, outf);
            }
        } else if (compare == "<>") {
            if (getValue(str) != num) {
                goToStatement(num2, outf);
            }
        }
        // if none of the comparison operators called, then error
        else {
            outf << "Invalid comparison operator" << endl;
            isBreak = true;
        }
    }
}

void ProgramState::goSubStatement(int n, std::ostream& outf) {
    lineStack.push(counter + 1);
    goToStatement(n, outf);
}

void ProgramState::returnStatement(std::ostream& outf) {
    // if return with no gosub, then end the program
    if (lineStack.empty()) {
        isBreak = true;
    } else {
        goToStatement(lineStack.top(), outf);
        lineStack.pop();
    }
}
