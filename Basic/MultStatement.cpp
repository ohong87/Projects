#include "MultStatement.h"

MultStatement::MultStatement(std::string s, int n) {
    num = n;
    str = s;
    str2 = "";
    isVar = false;
}

MultStatement::MultStatement(std::string s, std::string s2) {
    num = 0;
    str = s;
    str2 = s2;
    isVar = true;
}

void MultStatement::execute(ProgramState* state, std::ostream& outf) {
    // if str2 is a variable, then get it's value
    if (isVar) {
        num = state->getValue(str2);
        state->multStatement(str, num);
    } else {
        state->multStatement(str, num);
    }
    state->incrementCounter();
}