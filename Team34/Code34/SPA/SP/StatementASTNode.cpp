#include "StatementASTNode.h"
#include <iostream>
using namespace std;



LineIndex StatementASTNode::getLineIndex() {
	return lineIndex;
}

void StatementASTNode::setLineIndex(LineIndex& idx) {
	lineIndex = idx;
}

StatementType StatementASTNode::getStatementType() {
	return statement_type;
}

std::string StatementASTNode::getTypeVal() {
	return type_val;
}

void StatementASTNode::setStatementType(StatementType tp, string val) {
	statement_type = tp;
	type_val = val;
}
