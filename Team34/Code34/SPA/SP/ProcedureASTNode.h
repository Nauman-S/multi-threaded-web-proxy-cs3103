#pragma once

# include "ASTNode.h"
# include "StatementASTNode.h"
# include <vector>
# include <string>
# include"ProcedureIndex.h"
class ProcedureASTNode : public ASTNode {
public:
	ProcedureIndex getProc();

	std::vector<StatementASTNode> getChildren();

	void setProc(ProcedureIndex&);

	void setChildren(std::vector<StatementASTNode>&);

protected:
	ProcedureIndex proc;
	std::vector<StatementASTNode> children;
};
