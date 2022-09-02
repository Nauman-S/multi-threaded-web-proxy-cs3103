#pragma once

# include "ASTNode.h"
# include "StatementASTNode.h"
# include <vector>
# include <string>

class ProcedureASTNode : public ASTNode {
public:
	std::string getName();

	std::vector<StatementASTNode> getChildren();

	void setName(std::string);

	void setChildren(std::vector<StatementASTNode>&);

protected:
	std::string name;
	std::vector<StatementASTNode> children;
};
