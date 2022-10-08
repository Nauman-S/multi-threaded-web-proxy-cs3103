#include "ConditionExpression.h"

using namespace std;

void ConditionExpression::SetVariables(std::vector<Variable>& v) {
	vars = v;
}

std::vector<Variable> ConditionExpression::GetVariables() const {
	return vars;
}

std::vector<Constant> ConditionExpression::GetConstants() const {
	return cons;
}

void ConditionExpression::SetConstants(std::vector<Constant>& c) {
	cons = c;
}

void ConditionExpression::Extract(NodeExtractor& extractor) {
	extractor.ExtractConditionExpression(*this);
}
