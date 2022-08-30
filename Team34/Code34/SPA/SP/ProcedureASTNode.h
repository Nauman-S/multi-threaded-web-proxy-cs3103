#pragma once

# include "ASTNode.h"
# include "StatementASTNode.h"
# include <list>
# include <string>

class ProcedureASTNode : public ASTNode {
public:
	std::string getName() {
		return name;
	}

	std::list<StatementNode> getChildren() {
		return children;
	}

	void setName(nm) {
		name = nm;
	}

	void setChildren(std::list<StatementNode> chd) {
		children = chd
	}

protected:
	std::string name;
	std::list<StatementNode> children;
};