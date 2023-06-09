#include "ProgramState.h"
#include "Statement.h"
#include <string>

class IfStatement : public Statement {
public:
    IfStatement(std::string s, std::string s1, int n, int n1);
    virtual void execute(ProgramState* state, std::ostream& outf);

private:
    int num;
    int num2;
    std::string str;
    std::string str2;
};