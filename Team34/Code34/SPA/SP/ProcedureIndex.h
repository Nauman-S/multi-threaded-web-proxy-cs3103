#pragma once
# include <string>

class ProcedureIndex {
public:
	void setName(std::string);

	std::string getName();

protected:
	std::string procName;
};
