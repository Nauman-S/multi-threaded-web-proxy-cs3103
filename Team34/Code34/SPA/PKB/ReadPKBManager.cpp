#include "ReadPKBManager.h"

// APIs related to Variable entity
bool ReadPKBManager::IsVariable(Variable var) {
    return pkb.variable_manager_.IsEntity(var);
}

const std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetAllVariables() {
    return pkb.variable_manager_.GetAllEntities();
}

// APIs related to Constant entity
bool ReadPKBManager::IsConstant(Constant constant) {
    return pkb.constant_manager_.IsEntity(constant);
}

const std::shared_ptr<std::unordered_set<Constant>> ReadPKBManager::GetAllConstants() {
    return pkb.constant_manager_.GetAllEntities();
}

// APIs related to Procedure entity
bool ReadPKBManager::IsProcedure(Procedure proc) {
    return pkb.procedure_manager_.IsEntity(proc);
}

const std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllProcedures() {
    return pkb.procedure_manager_.GetAllEntities();
}

// APIs related to Statements
std::shared_ptr<RefType> ReadPKBManager::GetStatementType(StmtNum stmt_num) {
    return pkb.statement_manager_.GetStatementType(stmt_num);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetStatementsByType(RefType type) {
    return pkb.statement_manager_.GetStatementsByType(type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllStatements() {
    return pkb.statement_manager_.GetAllStatements();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetCallsStatementFromProcedure(Procedure proc) {
    return pkb.statement_manager_.GetCallsStatementFromProcedure(proc);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetPrintStatementFromVariable(Variable var) {
    return pkb.statement_manager_.GetPrintStatementFromVariable(var);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetReadStatementFromVariable(Variable var) {
    return pkb.statement_manager_.GetReadStatementFromVariable(var);
}

std::shared_ptr<Procedure> ReadPKBManager::GetCallsProcedureFromStatement(StmtNum stmt_num) {
    return pkb.statement_manager_.GetCallsProcedureFromStatement(stmt_num);
}

std::shared_ptr<Variable> ReadPKBManager::GetPrintVariableFromStatement(StmtNum stmt_num) {
    return pkb.statement_manager_.GetPrintVariableFromStatement(stmt_num);
}

std::shared_ptr<Variable> ReadPKBManager::GetReadVariableFromStatement(StmtNum stmt_num) {
    return pkb.statement_manager_.GetReadVariableFromStatement(stmt_num);
}

std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Procedure>>>> ReadPKBManager::GetAllCallsStatementProcedurePairs() {
    return pkb.statement_manager_.GetAllCallsStatementProcedurePairs();
}

std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Variable>>>> ReadPKBManager::GetAllPrintStatementVariablePairs() {
    return pkb.statement_manager_.GetAllPrintStatementVariablePairs();
}

std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<Variable>>>> ReadPKBManager::GetAllReadStatementVariablePairs() {
    return pkb.statement_manager_.GetAllReadStatementVariablePairs();
}

// APIs related to Parent relation
bool ReadPKBManager::CheckParent(StmtNum parent, StmtNum child) {
    return pkb.parent_manager_.CheckParent(parent, child);
}

bool ReadPKBManager::IsParentStoreEmpty() {
    return pkb.parent_manager_.IsEmpty();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetChildrenFromStmt(StmtNum parent, RefType children_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> children = pkb.parent_manager_.GetChildrenFromStmt(parent);
    return FilterStmtSetByType(children, children_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetParentFromStmt(StmtNum child, RefType parent_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> parent = pkb.parent_manager_.GetParentFromStmt(child);
    return FilterStmtSetByType(parent, parent_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllChildren(RefType children_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_children = pkb.parent_manager_.GetAllChildren();
    return FilterStmtSetByType(all_children, children_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllParents(RefType parent_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_parents = pkb.parent_manager_.GetAllParents();
    return FilterStmtSetByType(all_parents, parent_type);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllParentRelations() {
    return pkb.parent_manager_.GetAllParentRelations();
}

// APIs related to Parent* relation
bool ReadPKBManager::CheckParentT(StmtNum parent, StmtNum child) {
    return pkb.parent_manager_.CheckParentT(parent, child);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllChildrenFromStmt(StmtNum stmt, RefType children_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_children = pkb.parent_manager_.GetAllChildrenFromStmt(stmt);
    return FilterStmtSetByType(all_children, children_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllParentsFromStmt(StmtNum stmt, RefType parent_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_parents = pkb.parent_manager_.GetAllParentsFromStmt(stmt);
    return FilterStmtSetByType(all_parents, parent_type);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllParentTRelations() {
    return pkb.parent_manager_.GetAllParentTRelations();
}

// APIs related to Follows relation
bool ReadPKBManager::CheckFollows(StmtNum left, StmtNum right) {
    return pkb.follows_manager_.CheckFollows(left, right);
}

bool ReadPKBManager::IsFollowsStoreEmpty() {
    return pkb.follows_manager_.IsEmpty();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetSuccessorStmtFromStmt(StmtNum stmt, RefType successor_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> successor_stmt = pkb.follows_manager_.GetSuccessorStmtFromStmt(stmt);
    return FilterStmtSetByType(successor_stmt, successor_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetPredecessorStmtFromStmt(StmtNum stmt, RefType predecessor_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> predecessor_stmt = pkb.follows_manager_.GetPredecessorStmtFromStmt(stmt);
    return FilterStmtSetByType(predecessor_stmt, predecessor_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllSuccessorStmts(RefType successor_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_successor_stmts = pkb.follows_manager_.GetAllSuccessorStmts();
    return FilterStmtSetByType(all_successor_stmts, successor_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllPredecessorStmts(RefType predecessor_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_predecessor_stmts = pkb.follows_manager_.GetAllPredecessorStmts();
    return FilterStmtSetByType(all_predecessor_stmts, predecessor_type);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllFollowsRelations() {
    return pkb.follows_manager_.GetAllFollowsRelations();
}

// APIs related to Follows* relation
bool ReadPKBManager::CheckFollowsT(StmtNum left, StmtNum right) {
    return pkb.follows_manager_.CheckFollowsT(left, right);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllSuccessorStmtsFromStmt(StmtNum stmt, RefType successor_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> successor_stmts = pkb.follows_manager_.GetAllSuccessorStmtsFromStmt(stmt);
    return FilterStmtSetByType(successor_stmts, successor_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllPredecessorStmtsFromStmt(StmtNum stmt, RefType predecessor_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> predecessor_stmts = pkb.follows_manager_.GetAllPredecessorStmtsFromStmt(stmt);
    return FilterStmtSetByType(predecessor_stmts, predecessor_type);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllFollowsTRelations() {
    return pkb.follows_manager_.GetAllFollowsTRelations();
}

// APIs related to Uses relation
bool ReadPKBManager::CheckUses(StmtNum stmt_num, Variable var) {
    return pkb.uses_manager_.CheckUses(stmt_num, var);
}

bool ReadPKBManager::CheckUses(Procedure proc_name, Variable var) {
    return pkb.uses_manager_.CheckUses(proc_name, var);
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetUsesVarByStmtNum(StmtNum stmt_num) {
    return pkb.uses_manager_.GetVarByStmtNum(stmt_num);
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetUsesVarByProcName(Procedure proc_name) {
    return pkb.uses_manager_.GetVarByProcName(proc_name);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetUsesStmtNumByVar(Variable var, RefType stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> uses_stmts = pkb.uses_manager_.GetStmtNumByVar(var);
    return FilterStmtSetByType(uses_stmts, stmt_type);
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetUsesProcNameByVar(Variable var) {
    return pkb.uses_manager_.GetProcNameByVar(var);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllUsesStatements(RefType stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_uses_stmts = pkb.uses_manager_.GetAllStatements();
    return FilterStmtSetByType(all_uses_stmts, stmt_type);
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetAllUsesSVariables() {
    return pkb.uses_manager_.GetAllSVariables();
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllUsesProcedures() {
    return pkb.uses_manager_.GetAllProcedures();
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ReadPKBManager::GetAllSVUses() {
    return pkb.uses_manager_.GetAllSVUses();
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> ReadPKBManager::GetAllPVUses() {
    return pkb.uses_manager_.GetAllPVUses();
}

// APIs related to Modifies relation
bool ReadPKBManager::CheckModifies(StmtNum stmt_num, Variable var) {
    return pkb.modifies_manager_.CheckModifies(stmt_num, var);
}

bool ReadPKBManager::CheckModifies(Procedure proc_name, Variable var) {
    return pkb.modifies_manager_.CheckModifies(proc_name, var);
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetModifiesVarByStmtNum(StmtNum stmt_num) {
    return pkb.modifies_manager_.GetVarByStmtNum(stmt_num);
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetModifiesVarByProcName(Procedure proc_name) {
    return pkb.modifies_manager_.GetVarByProcName(proc_name);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetModifiesStmtNumByVar(Variable var, RefType stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> modifies_stmts = pkb.modifies_manager_.GetStmtNumByVar(var);
    return FilterStmtSetByType(modifies_stmts, stmt_type);
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetModifiesProcNameByVar(Variable var) {
    return pkb.modifies_manager_.GetProcNameByVar(var);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllModifiesStatements(RefType stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_modifies_stmts = pkb.modifies_manager_.GetAllStatements();
    return FilterStmtSetByType(all_modifies_stmts, stmt_type);
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetAllModifiesSVariables() {
    return pkb.modifies_manager_.GetAllSVariables();
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllModifiesProcedures() {
    return pkb.modifies_manager_.GetAllProcedures();
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ReadPKBManager::GetAllSVModifies() {
    return pkb.modifies_manager_.GetAllSVModifies();
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> ReadPKBManager::GetAllPVModifies() {
    return pkb.modifies_manager_.GetAllPVModifies();
}

// APIs related to Assign Pattern relation
std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::FilterByAssignPatternMatch(std::shared_ptr<ExprSpec> expr) {
    std::shared_ptr<std::unordered_set<StmtNum>> temp_set = pkb.statement_manager_.GetStatementsByType(RefType::kAssignRef);
    std::shared_ptr<std::unordered_set<StmtNum>> filtered_stmts = std::make_shared<std::unordered_set<StmtNum>>();
    for (auto stmt_num : *temp_set) {
        if (pkb.assign_pattern_manager_.IsPatternMatch(stmt_num, expr)) {
            filtered_stmts->insert(stmt_num);
        }
    }
    return filtered_stmts;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::FilterByAssignPatternMatch(Variable var, std::shared_ptr<ExprSpec> expr) {
    std::shared_ptr<std::unordered_set<StmtNum>> temp_set = pkb.modifies_manager_.GetStmtNumByVar(var);
    std::shared_ptr<std::unordered_set<StmtNum>> filtered_stmts = std::make_shared<std::unordered_set<StmtNum>>();
    for (auto stmt_num : *temp_set) {
        if (pkb.assign_pattern_manager_.IsPatternMatch(stmt_num, expr)) {
            filtered_stmts->insert(stmt_num);
        }
    }
    return filtered_stmts;
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ReadPKBManager::GetAssignPatternMatch(std::shared_ptr<ExprSpec> expr) {
    std::shared_ptr<std::unordered_set<StmtNum>> temp_set = pkb.statement_manager_.GetStatementsByType(RefType::kAssignRef);
    std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> filtered_stmts_with_var = std::make_shared<std::vector<std::pair<StmtNum, Variable>>>();
    for (auto stmt_num : *temp_set) {
        if (pkb.assign_pattern_manager_.IsPatternMatch(stmt_num, expr)) {
            std::shared_ptr<std::unordered_set<Variable>> vars = pkb.modifies_manager_.GetVarByStmtNum(stmt_num);
            for (auto iter = vars->begin(); iter != vars->end(); ++iter) {
                filtered_stmts_with_var->push_back(std::make_pair(stmt_num, *iter));
            }
        }
    }
    return filtered_stmts_with_var;
}

// APIs related to If Pattern relation
std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllIfPatternStatmentsFromVar(Variable var) {
    return pkb.if_pattern_manager_.GetAllStatmentsFromVar(var);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllIfPatternStatements() {
    return pkb.if_pattern_manager_.GetAllStatements();
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ReadPKBManager::GetAllIfPatterns() {
    return pkb.if_pattern_manager_.GetAllPatterns();
}

// APIs related to While Pattern relation
std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllWhilePatternStatmentsFromVar(Variable var) {
    return pkb.while_pattern_manager_.GetAllStatmentsFromVar(var);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllWhilePatternStatements() {
    return pkb.while_pattern_manager_.GetAllStatements();
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ReadPKBManager::GetAllWhilePatterns() {
    return pkb.while_pattern_manager_.GetAllPatterns();
}

// APIs related to Calls relation
bool ReadPKBManager::CheckCalls(Procedure caller, Procedure callee) {
    return pkb.calls_manager_.CheckCalls(caller, callee);
}

bool ReadPKBManager::IsCallsStoreEmpty() {
    return pkb.calls_manager_.IsEmpty();
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetCalleeFromCaller(Procedure caller) {
    return pkb.calls_manager_.GetCalleeFromCaller(caller);
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetCallerFromCallee(Procedure callee) {
    return pkb.calls_manager_.GetCallerFromCallee(callee);
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllCallers() {
    return pkb.calls_manager_.GetAllCallers();
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllCallees() {
    return pkb.calls_manager_.GetAllCallees();
}

std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> ReadPKBManager::GetAllCallsRelations() {
    return pkb.calls_manager_.GetAllCallsRelations();
}

// APIs related to Calls* relation
bool ReadPKBManager::CheckCallsT(Procedure caller, Procedure callee) {
    return pkb.calls_manager_.CheckCallsT(caller, callee);
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllCalleeFromCaller(Procedure caller) {
    return pkb.calls_manager_.GetAllCalleeFromCaller(caller);
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllCallerFromCallee(Procedure callee) {
    return pkb.calls_manager_.GetAllCallerFromCallee(callee);
}

std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> ReadPKBManager::GetAllCallsTRelations() {
    return pkb.calls_manager_.GetAllCallsTRelations();
}

// APIs related to Next relation
bool ReadPKBManager::CheckNext(StmtNum prev, StmtNum next) {
    return pkb.next_manager_.CheckNext(prev, next);
}

bool ReadPKBManager::IsNextStoreEmpty() {
    return pkb.next_manager_.IsEmpty();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetNextStmtsFromStmt(StmtNum stmt, RefType next_stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> next_stmts = pkb.next_manager_.GetNextStmtsFromStmt(stmt);
    return FilterStmtSetByType(next_stmts, next_stmt_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetPrevStmtsFromStmt(StmtNum stmt, RefType prev_stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> prev_stmts = pkb.next_manager_.GetPrevStmtsFromStmt(stmt);
    return FilterStmtSetByType(prev_stmts, prev_stmt_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllNextStmts(RefType next_stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_next_stmts = pkb.next_manager_.GetAllNextStmts();
    return FilterStmtSetByType(all_next_stmts, next_stmt_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllPrevStmts(RefType prev_stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_prev_stmts = pkb.next_manager_.GetAllPrevStmts();
    return FilterStmtSetByType(all_prev_stmts, prev_stmt_type);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllNextRelations() {
    return pkb.next_manager_.GetAllNextRelations();
}

// APIs related to Next* relation
bool ReadPKBManager::CheckNextT(StmtNum prev, StmtNum next) {
    return pkb.next_manager_.CheckNextT(prev, next);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllNextStmtsFromStmt(StmtNum stmt, RefType next_stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_next_stmts = pkb.next_manager_.GetAllNextStmtsFromStmt(stmt);
    return FilterStmtSetByType(all_next_stmts, next_stmt_type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllPrevStmtsFromStmt(StmtNum stmt, RefType prev_stmt_type) {
    std::shared_ptr<std::unordered_set<StmtNum>> all_prev_stmts = pkb.next_manager_.GetAllPrevStmtsFromStmt(stmt);
    return FilterStmtSetByType(all_prev_stmts, prev_stmt_type);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllNextTRelations() {
    return pkb.next_manager_.GetAllNextTRelations();
}

// APIs related to Affects relation
bool ReadPKBManager::CheckAffects(StmtNum cause, StmtNum effect) {
    return pkb.affects_manager_.CheckAffects(cause, effect);
}

bool ReadPKBManager::IsAffectsStoreEmpty() {
    return pkb.affects_manager_.IsEmpty();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetEffectStmtsFromStmt(StmtNum stmt, RefType effect_stmt_type) {
    if (effect_stmt_type != RefType::kStmtRef && effect_stmt_type != RefType::kAssignRef) {
        return std::make_shared<std::unordered_set<StmtNum>>();
    }
    return pkb.affects_manager_.GetEffectStmtsFromStmt(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetCauseStmtsFromStmt(StmtNum stmt, RefType cause_stmt_type) {
    if (cause_stmt_type != RefType::kStmtRef && cause_stmt_type != RefType::kAssignRef) {
        return std::make_shared<std::unordered_set<StmtNum>>();
    }
    return pkb.affects_manager_.GetCauseStmtsFromStmt(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllEffectStmts(RefType effect_stmt_type) {
    if (effect_stmt_type != RefType::kStmtRef && effect_stmt_type != RefType::kAssignRef) {
        return std::make_shared<std::unordered_set<StmtNum>>();
    }
    return pkb.affects_manager_.GetAllEffectStmts();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllCauseStmts(RefType cause_stmt_type) {
    if (cause_stmt_type != RefType::kStmtRef && cause_stmt_type != RefType::kAssignRef) {
        return std::make_shared<std::unordered_set<StmtNum>>();
    }
    return pkb.affects_manager_.GetAllCauseStmts();
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllAffectsRelations() {
    return pkb.affects_manager_.GetAllAffectsRelations();
}

// APIs related to Affects* relation
bool ReadPKBManager::CheckAffectsT(StmtNum cause, StmtNum effect) {
    return pkb.affects_manager_.CheckAffectsT(cause, effect);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllEffectStmtsFromStmt(StmtNum stmt, RefType effect_stmt_type) {
    if (effect_stmt_type != RefType::kStmtRef && effect_stmt_type != RefType::kAssignRef) {
        return std::make_shared<std::unordered_set<StmtNum>>();
    }
    return pkb.affects_manager_.GetAllEffectStmtsFromStmt(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllCauseStmtsFromStmt(StmtNum stmt, RefType cause_stmt_type) {
    if (cause_stmt_type != RefType::kStmtRef && cause_stmt_type != RefType::kAssignRef) {
        return std::make_shared<std::unordered_set<StmtNum>>();
    }
    return pkb.affects_manager_.GetAllCauseStmtsFromStmt(stmt);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllAffectsTRelations() {
    return pkb.affects_manager_.GetAllAffectsTRelations();
}

// Utility functions
std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::FilterStmtSetByType(std::shared_ptr<std::unordered_set<StmtNum>> stmts, RefType stmt_type) {
    if (stmt_type == RefType::kStmtRef) {
        return stmts;
    }

    auto res = std::make_shared<std::unordered_set<StmtNum>>();

    for (auto iter = stmts->begin(); iter != stmts->end(); ++iter) {
        if (*(pkb.statement_manager_.GetStatementType(*iter)) == stmt_type) {
            res->insert(*iter);
        }
    }

    return res;
}
