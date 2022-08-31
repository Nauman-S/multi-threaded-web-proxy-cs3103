#pragma once
# include "StatementASTNode.h"
# include <string>

class ConditionExpression : public StatementASTNode {
public:
	void setValue(std::string v) {
		value = v;
	}

	std::string getValue() {
		return value;
	}
protected:
    // need edit later
	std::string value;
};