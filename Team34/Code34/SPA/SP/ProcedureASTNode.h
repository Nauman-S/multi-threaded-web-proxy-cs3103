#pragma once

# include "ASTNode.h"
# include "StatementASTNode.h"
# include <list>
# include <string>

class ProcedureASTNode : public ASTNode {
public:
	std::string getName();

	std::list<StatementASTNode>* getChildren();

	void setName(std::string);

	void setChildren(std::list<StatementASTNode>*);

protected:
	std::string name;
	std::list<StatementASTNode>* children;
};
