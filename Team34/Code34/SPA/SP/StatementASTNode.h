#pragma once
# include "ASTNode.h"

class StatementNode : public ASTNode {
public:
	int getLineIndex() {
		return lineIndex;
	}

	void setLineIndex(num) {
		lineIndex = num;
	}

protected:
	int lineIndex;
};
