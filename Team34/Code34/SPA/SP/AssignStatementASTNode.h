#pragma once

# include "StatementASTNode.h"
# include "VariableIndex.h"
# include <vector>

class AssignStatementASTNode : public StatementASTNode {
public:
	void setLeft(VariableIndex&);

	void setRight(std::vector<VariableIndex>&);

	VariableIndex getLeft();

	std::vector<VariableIndex> getRight();

protected:
	VariableIndex left;
	std::vector<VariableIndex> right;
};
