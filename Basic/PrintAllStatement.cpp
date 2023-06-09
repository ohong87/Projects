#include "PrintAllStatement.h"

PrintAllStatement::PrintAllStatement() {}

void PrintAllStatement::execute(ProgramState* state, std::ostream& outf) {
    state->printAllStatement(outf);
    state->incrementCounter();
}