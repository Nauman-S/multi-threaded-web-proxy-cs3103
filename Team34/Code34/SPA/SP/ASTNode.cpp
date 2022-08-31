#include "ASTNode.h"

using namespace std;

void ASTNode::setParent(ASTNode* p) {
	parent = p;
}

ASTNode* ASTNode::getParent() {
	return parent;
}
