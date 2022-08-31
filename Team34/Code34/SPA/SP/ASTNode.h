#pragma once

class ASTNode {
public:
	void setParent(ASTNode p) {
		parent = p;
	}

	ASTNode getParent() {
		return parent;
	}

protected:
	ASTNode* parent = NULL;
};
