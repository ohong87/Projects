#include "SubStatement.h"

SubStatement::SubStatement(std::string s, int n) {
    num = n;
    str = s;
}

SubStatement::SubStatement(std::string s, std::string s2) {
    num = 0;
    str = s;
    str2 = s2;
    isVar = true;
}

void SubStatement::execute(ProgramState* state, std::ostream& outf) {
    // if str2 is a variable, then get it's value
    if (isVar) {
        num = state->getValue(str2);
        state->subStatement(str, num);
    } else {
        state->subStatement(str, num);
    }
    state->incrementCounter();
}