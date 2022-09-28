#include "ConditionExpression.h"

using namespace std;

void ConditionExpression::SetVariables(std::vector<Variable>& v) {
	vars = v;
}

std::vector<Variable> ConditionExpression::GetVariables() {
	return vars;
}

std::vector<Variable> ConditionExpression::GetConstants() {
	return cons;
}

void ConditionExpression::SetConstants(std::vector<Constant>& c) {
	cons = c;
}

void ConditionExpression::Extract(NodeExtractor& extractor) {
	extractor.ExtractConditionExpression(*this);
}