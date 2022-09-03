#pragma once

# include <vector>
# include "VariableIndex.h"
class VariableManager {
public:
	void addVariable(VariableIndex&);

	std::vector<VariableIndex> getVariables();

protected:
	std::vector<VariableIndex> variables;
};