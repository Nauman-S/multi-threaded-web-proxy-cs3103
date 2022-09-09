#pragma once
# include <vector>
# include <map>
# include <string>
# include "StatementASTNode.h"
# include "LineIndex.h"
# include "ProgramNode.h"

class DesignExtractor
{
public:
	std::vector<VariableIndex> getVariables(std::string& sourcefile);
	std::vector<int> getConstants(std::string& sourcefile);
	std::vector<ProcedureIndex> getProcedures(ProgramNode);
};

