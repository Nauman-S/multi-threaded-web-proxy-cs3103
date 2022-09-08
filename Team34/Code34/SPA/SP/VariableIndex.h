#pragma once
# include <string>

class VariableIndex {
public:
	void SetName(std::string nm);

	std::string GetName();

protected:
	std::string varName;
};
