#pragma once

# include "ASTNode.h"
# include "ProcedureASTNode.h"
# include<list>

class ProgramNode : ASTNode {
public:
	std::list<ProcedureASTNode> getChildren();

	void setChildren(std::list<ProcedureASTNode>*);

protected:
	std::list<ProcedureASTNode>* children;
};
