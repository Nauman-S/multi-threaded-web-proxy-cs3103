#pragma once
# include <string>

class ProcedureIndex {
public:
	void setName(std::string nm) {
		procName = nm;
	}

	std::string getName() {
		return procName;
	}

protected:
	std::string procName;
};
