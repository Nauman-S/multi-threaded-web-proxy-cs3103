#pragma once
# include <string>

class VariableIndex {
public:
	void setName(std::string nm);

	std::string getName();

protected:
	std::string varName;
};
