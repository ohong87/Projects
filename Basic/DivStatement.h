#include "ProgramState.h"
#include "Statement.h"
#include <string>

class DivStatement : public Statement {
public:
    DivStatement(std::string s, int n);
    DivStatement(std::string s, std::string s2);
    virtual void execute(ProgramState* state, std::ostream& outf);

private:
    int num;
    std::string str;
    std::string str2;
    bool isVar;
};