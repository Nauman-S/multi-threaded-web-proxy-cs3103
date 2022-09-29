#pragma once

# include <vector>
# include "StatementASTNode.h"
#include "../../Utils/type/TypeDef.h"

class AssignStatementASTNode : public StatementASTNode {
public:
	void SetLeft(Variable&);

	void SetInfix(string&);

	void SetRightVars(std::vector<Variable>&);

	void SetRightCons(std::vector<Constant>&);

	Variable GetLeft();

	std::string GetInfix();

	std::vector<Variable> GetRightVars();

	std::vector<Constant> GetRightCons();

	virtual void Extract(NodeExtractor&) override;


protected:
	Variable left;
	std::vector<Variable> right_vars;
	std::vector<Constant> right_cons;
	std::string infix;
};
