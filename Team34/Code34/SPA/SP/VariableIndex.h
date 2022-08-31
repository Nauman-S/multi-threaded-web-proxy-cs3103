#pragma once
# include <string>

class VariableIndex {
public:
	void setName(std::string nm) {
		varName = nm;
	}

	std::string getName() {
		return varName;
	}

protected:
	std::string varName;
};
