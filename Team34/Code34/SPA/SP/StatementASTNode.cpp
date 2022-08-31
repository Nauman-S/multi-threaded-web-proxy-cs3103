#include "StatementASTNode.h"

using namespace std;

LineIndex StatementASTNode::getLineIndex() {
	return *lineIndex;
}

void StatementASTNode::setLineIndex(LineIndex* idx) {
	lineIndex = idx;
}