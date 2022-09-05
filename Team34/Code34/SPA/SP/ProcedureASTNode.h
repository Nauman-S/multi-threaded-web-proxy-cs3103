#pragma once

#include <memory>
#include <vector>
#include <string>

#include "ASTNode.h"
#include "StatementASTNode.h"
#include"ProcedureIndex.h"

class ProcedureASTNode : public ASTNode {
public:
	ProcedureIndex getProc();

	std::vector<std::shared_ptr<StatementASTNode>> getChildren();

	void setProc(ProcedureIndex&);

	void setChildren(std::vector<std::shared_ptr<StatementASTNode>>&);

	virtual void Extract(NodeExtractor&);

protected:
	ProcedureIndex proc;
	std::vector<std::shared_ptr<StatementASTNode>> children;
};
