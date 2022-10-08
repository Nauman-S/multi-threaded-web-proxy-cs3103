#include "ReadStatementASTNode.h"
#include <iostream>
using namespace std;

void ReadStatementASTNode::SetVariable(Variable& v) {
	var = v;
}

Variable ReadStatementASTNode::GetReadVariable() const {
	return var;
}

void ReadStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractReadNode(*this);
}
