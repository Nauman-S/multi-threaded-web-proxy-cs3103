#include "ReadStatementASTNode.h"
#include "design_extractor/NodeExtractor.h"

using namespace std;

void ReadStatementASTNode::setVariable(VariableIndex* v) {
	var = v;
}

VariableIndex ReadStatementASTNode::getVariable() {
	return *var;
}

void ReadStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractReadNode();
}

