#pragma once

class ASTNode {
public:
	void setParent(ASTNode*);

	ASTNode* getParent();

protected:
	ASTNode* parent;
};
