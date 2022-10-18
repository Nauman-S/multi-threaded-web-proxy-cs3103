#pragma once

# include <vector>
# include <string>
# include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class AssignStatementASTNode : public StatementASTNode {
public:
    void SetLeft(Variable&);
    void SetInfix(string&);
    void SetRightVars(std::vector<Variable>&);
    void SetRightCons(std::vector<Constant>&);

    Variable GetLeft() const;
    std::string GetInfix() const;
    std::vector<Variable> GetRightVars() const;
    std::vector<Constant> GetRightCons() const;

    virtual void Extract(NodeExtractor&) override;
    virtual string Stringify() override;

protected:
    Variable left;
    std::vector<Variable> right_vars;
    std::vector<Constant> right_cons;
    std::string infix;
};
