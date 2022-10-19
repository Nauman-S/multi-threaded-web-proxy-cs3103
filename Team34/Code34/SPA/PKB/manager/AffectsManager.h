#pragma once

#include <memory>
#include <unordered_set>
#include <vector>
#include <queue>

#include "../../Utils/type/TypeDef.h"
#include "../../Utils/type/RefType.h"

class AffectsManager {
public:
    // Affects Relation methods
    bool CheckAffects(StmtNum cause, StmtNum effect);
    bool IsEmpty();
    std::shared_ptr<std::unordered_set<StmtNum>> GetEffectStmtsFromStmt(StmtNum stmt);
    std::shared_ptr<std::unordered_set<StmtNum>> GetCauseStmtsFromStmt(StmtNum stmt);
    std::shared_ptr<std::unordered_set<StmtNum>> GetAllEffectStmts();
    std::shared_ptr<std::unordered_set<StmtNum>> GetAllCauseStmts();
    std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllAffectsRelations();

    // Affects* Relation methods
    bool CheckAffectsT(StmtNum cause, StmtNum effect);
    std::shared_ptr<std::unordered_set<StmtNum>> GetAllEffectStmtsFromStmt(StmtNum stmt);
    std::shared_ptr<std::unordered_set<StmtNum>> GetAllCauseStmtsFromStmt(StmtNum stmt);
    std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllAffectsTRelations();
private:
    bool IsPossibleAffectPair(StmtNum, StmtNum);
    bool IsDirectlyModified(Variable, StmtNum);
    void AddEffectsStmtsBFS(std::shared_ptr<std::unordered_set<StmtNum>> effect_stmts, Variable modified_var, StmtNum stmt);
    void AddEffectsStmtsIfUsingVar(StmtNum stmt, std::unordered_set<StmtNum>& visited, std::queue<StmtNum>& queue, std::shared_ptr<std::unordered_set<StmtNum>> effect_stmts, Variable modified_var);
    void AddCauseStmtsBFS(std::shared_ptr<std::unordered_set<StmtNum>> cause_stmts, Variable used_var, StmtNum stmt);
    void AddCauseStmtsIfModifyingVar(StmtNum stmt, std::unordered_set<StmtNum>& visited, std::queue<StmtNum>& queue, std::shared_ptr<std::unordered_set<StmtNum>> cause_stmts, Variable used_var);
    bool IsAssignStatementModifyingVariable(Variable var, StmtNum stmt);
    bool IsAssignStatementUsingVariable(Variable var, StmtNum stmt);
    Variable GetModifiedVarInAssign(StmtNum);
    bool IsStatementType(StmtNum, RefType);
    bool IsAssignStmt(StmtNum);
    bool IsReadStmt(StmtNum);
    bool IsCallStmt(StmtNum);
    void GenerateAffectsPairs(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_affects_relations, StmtNum lhs, std::shared_ptr<std::unordered_set<StmtNum>> rhs);
};