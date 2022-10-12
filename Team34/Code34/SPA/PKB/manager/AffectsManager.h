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
	bool IsEmpty();
	std::shared_ptr<std::unordered_set<StmtNum>> GetEffectStmtsFromStmt(StmtNum stmt, RefType effect_stmt_type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetCauseStmtsFromStmt(StmtNum stmt, RefType effect_stmt_type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllEffectStmts(RefType effect_stmt_type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllCauseStmts(RefType cause_stmt_type);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllAffectsRelations();

	// Affects* Relation methods
	bool CheckAffectsT(StmtNum cause, StmtNum effect);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllEffectStmtsFromStmt(StmtNum stmt, RefType effect_stmt_type);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllCauseStmtsFromStmt(StmtNum stmt, RefType cause_stmt_type);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllAffectsTRelations();
private:
	bool IsPossibleAffectPair(StmtNum, StmtNum);
	bool IsDirectlyModified(Variable, StmtNum);

	Variable GetModifiedVarInAssign(StmtNum);
	bool IsStatementType(StmtNum, RefType);
	bool IsAssignStmt(StmtNum);
	bool IsReadStmt(StmtNum);
	bool IsCallStmt(StmtNum);
};