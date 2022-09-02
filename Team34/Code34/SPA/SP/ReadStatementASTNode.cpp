#include "ReadStatementASTNode.h"

using namespace std;

void ReadStatementASTNode::setVariable(VariableIndex& v) {
	var = v;
}

VariableIndex ReadStatementASTNode::getVariable() {
	return var;
}