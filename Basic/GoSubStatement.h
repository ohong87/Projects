#include "ProgramState.h"
#include "Statement.h"
#include <string>

class GoSubStatement : public Statement {
public:
    GoSubStatement(int n);
    virtual void execute(ProgramState* state, std::ostream& outf);

private:
    int num;
};