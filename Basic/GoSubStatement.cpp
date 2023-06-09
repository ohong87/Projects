#include "GoSubStatement.h"

GoSubStatement::GoSubStatement(int n) { num = n; }

void GoSubStatement::execute(ProgramState* state, std::ostream& outf) {
    state->goSubStatement(num, outf);
    state->incrementCounter();
}