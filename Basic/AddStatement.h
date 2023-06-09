#include "ProgramState.h"
#include "Statement.h"
#include <string>

class AddStatement : public Statement {
public:
    AddStatement(std::string s, int n);
    AddStatement(std::string s, std::string s2);
    virtual void execute(ProgramState* state, std::ostream& outf);

private:
    int num;
    std::string str;
    std::string str2;
    bool isVar;
};