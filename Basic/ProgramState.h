// ProgramState.h
//
// CS 104 / Fall 2021
//
// The ProgramState class encapsulates the state of an executing Facile
// program.  The state of a BASIC program consists of three parts:
//
//    * The program counter, which specifies the line number of the
//      statement that will execute next.
//    * A map, as explained by the problem writeup.
//    * A stack of integers, which is used to hold return lines for GOSUB
//      statements.
//
// We've provided you a start on this class, but you'll need to add methods
// to it as you go along.  In particular, you'll need methods to access and
// modify the state; these methods will be called primarily by the various
// execute() methods in the Statement subclasses, to allow the execution of
// a statement to change the state of a program.  For example, executing a
// GOTO statement will cause the program counter to be changed.

#ifndef PROGRAM_STATE_INCLUDED
#define PROGRAM_STATE_INCLUDED

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>

class ProgramState {
public:
    ProgramState(int numLines);

    // You'll need to add a variety of methods here.  Rather than trying to
    // think of what you'll need to add ahead of time, add them as you find
    // that you need them.
    void incrementCounter();
    void letStatement(std::string str, int num);

    void setIsEnd();
    bool getIsEnd();

    // std::map<std::string, int> printStatement();

    int getLineNumber();
    int getValue(std::string str);

    void printStatement(std::string str, std::ostream& outf);
    void printAllStatement(std::ostream& outf);

    void addStatement(std::string s, int n);
    void subStatement(std::string s, int n);
    void multStatement(std::string s, int n);
    void divStatement(std::string s, int n);

    void goToStatement(int n, std::ostream& outf);

    void setBreak();
    bool getBreak();

    void ifStatement(std::string str, std::string compare, int num, int num2, std::ostream& outf);

    void goSubStatement(int n, std::ostream& outf);
    void returnStatement(std::ostream& outf);

private:
    int m_numLines;
    int counter;
    bool isEnd;
    bool isBreak;
    std::map<std::string, int> var;
    std::stack<int> lineStack;
};

#endif
