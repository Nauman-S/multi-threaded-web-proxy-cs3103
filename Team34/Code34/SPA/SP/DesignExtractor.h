#pragma once
# include <vector>
# include <map>
#include <memory>
# include <string>
# include "StatementASTNode.h"
# include "LineIndex.h"
# include "ProgramNode.h"

class DesignExtractor
{
public:
	std::vector<VariableIndex> GetVariables(std::string& sourcefile);
	std::vector<int> GetConstants(std::string& sourcefile);
	std::vector<ProcedureIndex> GetProcedures(shared_ptr<ProgramNode>);
};

