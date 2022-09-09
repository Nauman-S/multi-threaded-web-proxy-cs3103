#pragma once

#include <memory>
#include <vector>
#include <string>

#include "ASTNode.h"
#include "StatementASTNode.h"
#include"ProcedureIndex.h"

class ProcedureASTNode : public ASTNode {
public:
	ProcedureIndex GetProc();

	std::vector<std::shared_ptr<StatementASTNode>> GetChildren();

	void SetProc(ProcedureIndex&);

	void SetChildren(std::vector<std::shared_ptr<StatementASTNode>>&);

	virtual void Extract(NodeExtractor&) override;

protected:
	ProcedureIndex proc;
	std::vector<std::shared_ptr<StatementASTNode>> children;
};
