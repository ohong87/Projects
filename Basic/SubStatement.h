#include "ProgramState.h"
#include "Statement.h"
#include <string>

class SubStatement : public Statement {
public:
    SubStatement(std::string s, int n);
    SubStatement(std::string s, std::string s2);
    virtual void execute(ProgramState* state, std::ostream& outf);

private:
    int num;
    std::string str;
    std::string str2;
    bool isVar;
};