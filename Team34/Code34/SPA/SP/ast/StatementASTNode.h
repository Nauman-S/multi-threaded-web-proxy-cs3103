#pragma once

#include <string>
#include <vector>

#include "ASTNode.h"
#include "../../Utils/type/TypeDef.h"

class StatementASTNode : public ASTNode {
public:
	StmtNum GetLineIndex();

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
};