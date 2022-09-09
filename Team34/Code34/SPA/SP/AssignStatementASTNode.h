#pragma once

# include <vector>
# include "StatementASTNode.h"
# include "VariableIndex.h"


class AssignStatementASTNode : public StatementASTNode {
public:
	void SetLeft(VariableIndex&);

	void SetRight(std::vector<VariableIndex>&);

	VariableIndex GetLeft();

	std::vector<VariableIndex> GetRight();

	virtual void Extract(NodeExtractor&) override;

protected:
	VariableIndex left;
	std::vector<VariableIndex> right;
};
