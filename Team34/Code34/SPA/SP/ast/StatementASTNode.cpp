#include "StatementASTNode.h"
#include <iostream>
using namespace std;



StmtNum StatementASTNode::GetLineIndex() {
	return lineIndex;
}

void StatementASTNode::SetLineIndex(StmtNum& idx) {
	lineIndex = idx;
}	


std::string StatementASTNode::GetTypeVal() {
	return type_val;
}

void StatementASTNode::SetStatementType(StatementType tp, string val) {
	statement_type = tp;
	type_val = val;
}

void StatementASTNode::SetParentSatementLineIndex(StmtNum& l) {
	parent_stmt = l;
}

StmtNum StatementASTNode::GetParentSatementLineIndex() {
	return parent_stmt;
}

void StatementASTNode::SetParentProcIndex(Procedure& p) {
	parent_proc = p;
}

Procedure StatementASTNode::GetParentProcIndex() {
	return parent_proc;
}