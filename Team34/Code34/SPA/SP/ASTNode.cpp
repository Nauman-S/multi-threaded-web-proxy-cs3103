#include "ASTNode.h"

using namespace std;

void ASTNode::SetParent(shared_ptr<ASTNode> p) {
	parent = p;
}

shared_ptr<ASTNode> ASTNode::GetParent() {
	return parent;
}
