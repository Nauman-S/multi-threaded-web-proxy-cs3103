#pragma once
# include "ASTNode.h"
# include "LineIndex.h"

class StatementASTNode : public ASTNode {
public:
	LineIndex getLineIndex();

	void setLineIndex(LineIndex*);

protected:
	LineIndex* lineIndex;
};
