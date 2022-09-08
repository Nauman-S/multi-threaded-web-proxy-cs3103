#include "ConditionExpression.h"

#include "design_extractor/NodeExtractor.h"

using namespace std;

void ConditionExpression::setVariables(std::vector<VariableIndex>& v) {
	vars = v;
}

std::vector<VariableIndex> ConditionExpression::getVariables() {
	return vars;
}

void ConditionExpression::Extract(NodeExtractor& extractor) {
	extractor.ExtractConditionExpression(*this);
}

