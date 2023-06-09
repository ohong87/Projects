#include "ReturnStatement.h"

ReturnStatement::ReturnStatement() {}

void ReturnStatement::execute(ProgramState* state, std::ostream& outf) {
    state->returnStatement(outf);
    state->incrementCounter();
}