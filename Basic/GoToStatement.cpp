#include "GoToStatement.h"

GoToStatement::GoToStatement(int n) { num = n; }

void GoToStatement::execute(ProgramState* state, std::ostream& outf) {
    state->goToStatement(num, outf);
    state->incrementCounter();
}
