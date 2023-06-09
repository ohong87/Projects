#include "ProgramState.h"
#include "Statement.h"
#include <string>

class GoToStatement : public Statement {
public:
    GoToStatement(int n);
    virtual void execute(ProgramState* state, std::ostream& outf);

private:
    int num;
};