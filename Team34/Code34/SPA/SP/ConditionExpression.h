#pragma once
# include "StatementASTNode.h"
# include <string>

class ConditionExpression : public StatementASTNode {
public:
	void setValue(std::string);

	std::string getValue();

protected:
    // need edit later
	std::string value;
};