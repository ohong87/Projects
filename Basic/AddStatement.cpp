#include "AddStatement.h"

AddStatement::AddStatement(std::string s, int n) {
    num = n;
    str = s;
    str2 = "";
    isVar = false;
}

AddStatement::AddStatement(std::string s, std::string s2) {
    num = 0;
    str = s;
    str2 = s2;
    isVar = true;
}

void AddStatement::execute(ProgramState* state, std::ostream& outf) {
    // if str2 is a variable, then get its value
    if (isVar) {
        num = state->getValue(str2);
        state->addStatement(str, num);
    } else {
        state->addStatement(str, num);
    }
    state->incrementCounter();
}