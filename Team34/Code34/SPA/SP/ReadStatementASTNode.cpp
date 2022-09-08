#include "ReadStatementASTNode.h"
#include <iostream>
using namespace std;

void ReadStatementASTNode::SetVariable(VariableIndex& v) {
	var = v;
}

VariableIndex ReadStatementASTNode::GetReadVariable() {
	return var;
}

void ReadStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractReadNode(*this);
}
