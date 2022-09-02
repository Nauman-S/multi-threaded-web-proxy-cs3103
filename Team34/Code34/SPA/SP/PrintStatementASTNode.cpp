# include "PrintStatementASTNode.h"

using namespace std;

void PrintStatementASTNode::setVariable(VariableIndex& v) {
	var = v;
}

VariableIndex PrintStatementASTNode::getVariable() {
	return var;
}