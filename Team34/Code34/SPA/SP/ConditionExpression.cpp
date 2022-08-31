#include "ConditionExpression.h"

using namespace std;

void ConditionExpression::setValue(std::string v) {
	value = v;
}

std::string ConditionExpression::getValue() {
	return value;
}