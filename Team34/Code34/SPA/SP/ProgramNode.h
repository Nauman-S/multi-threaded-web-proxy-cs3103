#pragma once

#include<vector>

#include "ASTNode.h"
#include "ProcedureASTNode.h"

class ProgramNode : ASTNode {
public:
	std::vector<ProcedureASTNode> getChildren();

	void setChildren(std::vector<ProcedureASTNode>&);

	virtual void Extract(NodeExtractor&) override;

protected:
	std::vector<ProcedureASTNode> children;
};
