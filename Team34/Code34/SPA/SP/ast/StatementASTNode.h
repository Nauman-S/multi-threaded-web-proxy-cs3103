#pragma once

#include <string>
#include <vector>

#include "ASTNode.h"
#include "../../Utils/type/TypeDef.h"

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
	StmtNum GetLineIndex();

	StatementType GetStatementType();

	std::string GetTypeVal();

	void SetStatementType(StatementType, std::string);

	void SetLineIndex(StmtNum&);

	bool operator < (const StatementASTNode& c) const
	{
		return lineIndex < c.lineIndex;
	}

	void SetParentSatementLineIndex(StmtNum&);

	StmtNum GetParentSatementLineIndex();

	void SetParentProcIndex(Procedure&);

	Procedure GetParentProcIndex();

	virtual void Extract(NodeExtractor&) = 0;
	// virtual vector<VariableIndex> getModifies() = 0;

protected:
	StmtNum lineIndex;
	StmtNum parent_stmt;
	Procedure parent_proc;
	StatementType statement_type;
	std::string type_val;
};
