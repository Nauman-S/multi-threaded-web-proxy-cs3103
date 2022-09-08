#include "StatementASTNode.h"
#include <iostream>
using namespace std;



LineIndex StatementASTNode::GetLineIndex() {
	return lineIndex;
}

void StatementASTNode::SetLineIndex(LineIndex& idx) {
	lineIndex = idx;
}	

StatementType StatementASTNode::GetStatementType() {
	return statement_type;
}

std::string StatementASTNode::GetTypeVal() {
	return type_val;
}

void StatementASTNode::SetStatementType(StatementType tp, string val) {
	statement_type = tp;
	type_val = val;
}
