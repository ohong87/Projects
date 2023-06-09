// PrintStatement.cpp:
#include "PrintStatement.h"

PrintStatement::PrintStatement(std::string variableName) : m_variableName(variableName) {}

void PrintStatement::execute(ProgramState* state, std::ostream& outf) {
    state->printStatement(m_variableName, outf);
    state->incrementCounter();
}
