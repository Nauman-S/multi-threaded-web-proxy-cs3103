#include "ReadStatementASTNode.h"
#include <iostream>
using namespace std;

void ReadStatementASTNode::setVariable(VariableIndex& v) {
	var = v;
}

VariableIndex ReadStatementASTNode::getReadVariable() {
	return var;
}

void ReadStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractReadNode(*this);
}
