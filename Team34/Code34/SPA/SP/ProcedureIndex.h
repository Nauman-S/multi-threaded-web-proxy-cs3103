#pragma once
# include <string>

class ProcedureIndex {
public:
	void SetName(std::string);

	std::string GetName();

protected:
	std::string procName;
};
