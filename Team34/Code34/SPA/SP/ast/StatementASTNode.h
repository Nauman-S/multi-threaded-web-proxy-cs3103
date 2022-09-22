#pragma once

#include <string>
#include <vector>

#include "ASTNode.h"
#include "../LineIndex.h"
#include "../VariableIndex.h"
#include "../ProcedureIndex.h"

enum class StatementType {
	sassign,
	sif,
	swhile,
	sexpre,
	sprint,
	sread,
	scall,
};

class StatementASTNode : public ASTNode {
public:
	LineIndex GetLineIndex();

	void SetLineIndex(LineIndex&);

	StatementType GetStatementType();

	std::string GetTypeVal();

	void SetStatementType(StatementType, std::string);

	bool operator < (const StatementASTNode& c) const
	{
		return lineIndex < c.lineIndex;
	}

	void SetParentSatementLineIndex(LineIndex&);

	LineIndex GetParentSatementLineIndex();

	void SetParentProcIndex(ProcedureIndex&);

	ProcedureIndex GetParentProcIndex();

	virtual void Extract(NodeExtractor&) = 0;
	// virtual vector<VariableIndex> getModifies() = 0;

protected:
	LineIndex lineIndex;
	StatementType statement_type;
	std::string type_val;
	LineIndex parent_stmt;
	ProcedureIndex parent_proc;
};
