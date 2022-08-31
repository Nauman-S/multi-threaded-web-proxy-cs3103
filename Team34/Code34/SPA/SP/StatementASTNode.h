#pragma once
# include "ASTNode.h"
# include "LineIndex.h"

class StatementASTNode : public ASTNode {
public:
	LineIndex getLineIndex() {
		return lineIndex;
	}

	void setLineIndex(LineIndex idx) {
		lineIndex = idx;
	}

protected:
	int lineIndex;
};
