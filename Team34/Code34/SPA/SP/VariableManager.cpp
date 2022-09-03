# include "VariableManager.h"

void VariableManager::addVariable(VariableIndex* var) {
	variables->push_back(*var);
}

std::vector<VariableIndex> VariableManager::getVariables() {
	return *variables;
}