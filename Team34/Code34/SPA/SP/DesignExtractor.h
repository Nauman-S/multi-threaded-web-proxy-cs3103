#pragma once
# include <vector>
# include <map>
# include <string>
# include "StatementASTNode.h"
# include "LineIndex.h"
# include "VariableManager.h"
# include "ConstantManager.h"
# include "ProcedureManager.h"
# include "ProgramNode.h"
class DesignExtractor
{
public:
	VariableManager getVariables(std::string &sourcefile);
	ConstantManager getConstants(std::string& sourcefile);
	ProcedureManager getProcedures(ProgramNode);
};

