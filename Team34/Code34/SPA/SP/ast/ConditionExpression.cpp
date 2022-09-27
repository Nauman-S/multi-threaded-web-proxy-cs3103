#include "ConditionExpression.h"

using namespace std;

void ConditionExpression::SetVariables(std::vector<Variable>& v) {
	vars = v;
}

std::vector<Variable> ConditionExpression::GetVariables() {
	return vars;
}

void ConditionExpression::Extract(NodeExtractor& extractor) {
	extractor.ExtractConditionExpression(*this);
}