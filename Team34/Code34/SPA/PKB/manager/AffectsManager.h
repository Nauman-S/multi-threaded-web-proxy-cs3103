#pragma once

#include <memory>
#include <unordered_set>
#include <vector>

#include "../../Utils/type/TypeDef.h"
#include "../../Utils/type/RefType.h"

class AffectsManager
{
public:
	// Affects Relation methods
	bool CheckAffects(StmtNum cause, StmtNum effect);

private:
	bool IsPossibleAffectPair(StmtNum, StmtNum);
	bool IsDirectlyModified(Variable, StmtNum);

	Variable GetModifiedVarInAssign(StmtNum);
	bool IsStatementType(StmtNum, RefType);
	bool IsAssignStmt(StmtNum);
	bool IsReadStmt(StmtNum);
	bool IsCallStmt(StmtNum);
};