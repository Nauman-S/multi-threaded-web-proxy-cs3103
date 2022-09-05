#pragma once

#include<vector>

#include "ASTNode.h"
#include "ProcedureASTNode.h"
#include "design_extractor/Extractable.h"

class ProgramNode : ASTNode, public Extractable {
public:
	std::vector<ProcedureASTNode> getChildren();

	void setChildren(std::vector<ProcedureASTNode>&);

	virtual void Extract(NodeExtractor&);

protected:
	std::vector<ProcedureASTNode> children;
};
