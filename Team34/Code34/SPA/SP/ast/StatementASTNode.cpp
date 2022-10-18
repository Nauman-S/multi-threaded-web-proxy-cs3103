#include "StatementASTNode.h"
#include <iostream>

using namespace std;

StmtNum StatementASTNode::GetLineIndex() const {
    return lineIndex;
}

void StatementASTNode::SetLineIndex(StmtNum& idx) {
    lineIndex = idx;
}

void StatementASTNode::SetParentSatementLineIndex(StmtNum& l) {
    parent_stmt = l;
}

StmtNum StatementASTNode::GetParentSatementLineIndex() const {
    return parent_stmt;
}

void StatementASTNode::SetParentProcIndex(Procedure& p) {
    parent_proc = p;
}

Procedure StatementASTNode::GetParentProcIndex() const {
    return parent_proc;
}