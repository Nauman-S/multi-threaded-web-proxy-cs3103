#pragma once

# include "ASTNode.h"
# include "ProcedureASTNode.h"
# include<vector>

class ProgramNode : ASTNode {
public:
	std::vector<ProcedureASTNode> getChildren();

	void setChildren(std::vector<ProcedureASTNode>&);

protected:
	std::vector<ProcedureASTNode> children;
};
