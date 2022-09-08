#pragma once

#include<vector>
#include <memory>
#include "ASTNode.h"
#include "ProcedureASTNode.h"

class ProgramNode : ASTNode {
public:
	std::vector<std::shared_ptr<ProcedureASTNode>> GetChildren();

	void SetChildren(std::vector<std::shared_ptr<ProcedureASTNode>>);

	virtual void Extract(NodeExtractor&) override;

protected:
	std::vector<std::shared_ptr<ProcedureASTNode>> children;
};
