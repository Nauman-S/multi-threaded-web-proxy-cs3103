#include "ConditionExpression.h"

using namespace std;

void ConditionExpression::SetVariables(std::vector<VariableIndex>& v) {
	vars = v;
}

std::vector<VariableIndex> ConditionExpression::GetVariables() {
	return vars;
}

void ConditionExpression::Extract(NodeExtractor& extractor) {
	extractor.ExtractConditionExpression(*this);
}