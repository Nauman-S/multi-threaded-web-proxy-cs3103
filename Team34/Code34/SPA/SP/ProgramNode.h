#pragma once

# include "ASTNode.h"
# include "ProcedureASTNode.h"
# include<list>

class ProgramNode : ASTNode {
public:
	std::list<ProcedureASTNode> getChildren() {
		return children;
	}

	void setChildren(std::list<ProcedureASTNode> chd) {
		children = chd;
	}
protected:
	std::list<ProcedureASTNode> children;
};
