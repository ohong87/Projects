#include "IfStatement.h"

IfStatement::IfStatement(std::string s, std::string s1, int n, int n1) {
    str = s;
    str2 = s1;
    num = n;
    num2 = n1;
}

void IfStatement::execute(ProgramState* state, std::ostream& outf) {
    state->ifStatement(str, str2, num, num2, outf);
    state->incrementCounter();
}