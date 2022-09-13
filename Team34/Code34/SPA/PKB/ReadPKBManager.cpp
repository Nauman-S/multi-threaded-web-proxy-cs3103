#include "ReadPKBManager.h"

// APIs related to Variable entity
bool ReadPKBManager::IsVariable(Variable var)
{
    return pkb.variable_manager_.IsEntity(var);
}

const std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetAllVariables()
{
	return pkb.variable_manager_.GetAllEntities();
}

// APIs related to Constant entity
bool ReadPKBManager::IsConstant(Constant constant)
{
    return pkb.constant_manager_.IsEntity(constant);
}

const std::shared_ptr<std::unordered_set<Constant>> ReadPKBManager::GetAllConstants()
{
	return pkb.constant_manager_.GetAllEntities();
}

// APIs related to Procedure entity
bool ReadPKBManager::IsProcedure(Procedure proc)
{
	return pkb.procedure_manager_.IsEntity(proc);
}

const std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllProcedures()
{
	return pkb.procedure_manager_.GetAllEntities();
}


// APIs related to Statements
bool ReadPKBManager::IsStatement(StmtNum stmt_num)
{
	return pkb.statement_manager_.IsStatement(stmt_num);
}

RefType ReadPKBManager::GetStatementType(StmtNum stmt_num)
{
	return pkb.statement_manager_.GetStatementType(stmt_num);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetStatementsByType(RefType type)
{
	return pkb.statement_manager_.GetStatementsByType(type);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllStatements()
{
	return pkb.statement_manager_.GetAllStatements();
}

// APIs related to Parent relation
bool ReadPKBManager::CheckParent(StmtNum parent, StmtNum child)
{
	return pkb.parent_manager_.CheckParent(parent, child);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetChildrenFromStmt(StmtNum parent)
{
	return pkb.parent_manager_.GetChildrenFromStmt(parent);
}

StmtNum ReadPKBManager::GetParentFromStmt(StmtNum child)
{
	return pkb.parent_manager_.GetParentFromStmt(child);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllParentRelations()
{
	return pkb.parent_manager_.GetAllParentRelations();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllParents()
{
	return pkb.parent_manager_.GetAllParents();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllChildren()
{
	return pkb.parent_manager_.GetAllChildren();
}

bool ReadPKBManager::IsParentStoreEmpty()
{
	return pkb.parent_manager_.IsEmpty();
}

// APIs related to Parent* relation
bool ReadPKBManager::CheckParentT(StmtNum parent, StmtNum child)
{
	return pkb.parent_manager_.CheckParentT(parent, child);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllChildrenFromStmt(StmtNum stmt)
{
	return pkb.parent_manager_.GetAllChildrenFromStmt(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllParentsFromStmt(StmtNum stmt)
{
	return pkb.parent_manager_.GetAllParentsFromStmt(stmt);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllParentTRelations()
{
	return pkb.parent_manager_.GetAllParentTRelations();
}

// APIs related to Follows relation
bool ReadPKBManager::CheckFollows(StmtNum left, StmtNum right)
{
	return pkb.follows_manager_.CheckFollows(left, right);
}

StmtNum ReadPKBManager::GetSuccessorStmtFromStmt(StmtNum stmt)
{
	return pkb.follows_manager_.GetSuccessorStmtFromStmt(stmt);
}

StmtNum ReadPKBManager::GetPredecessorStmtFromStmt(StmtNum stmt)
{
	return pkb.follows_manager_.GetPredecessorStmtFromStmt(stmt);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllFollowsRelations()
{
	return pkb.follows_manager_.GetAllFollowsRelations();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllPredecessorStmts()
{
	return pkb.follows_manager_.GetAllPredecessorStmts();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllSuccessorStmts()
{
	return pkb.follows_manager_.GetAllSuccessorStmts();
}

bool ReadPKBManager::IsFollowsStoreEmpty()
{
	return pkb.follows_manager_.IsEmpty();
}

// APIs related to Follows* relation
bool ReadPKBManager::CheckFollowsT(StmtNum left, StmtNum right)
{
	return pkb.follows_manager_.CheckFollowsT(left, right);
}

std::shared_ptr<std::vector<StmtNum>> ReadPKBManager::GetAllSuccessorStmtsFromStmt(StmtNum stmt)
{
	return pkb.follows_manager_.GetAllSuccessorStmtsFromStmt(stmt);
}

std::shared_ptr<std::vector<StmtNum>> ReadPKBManager::GetAllPredecessorStmtsFromStmt(StmtNum stmt)
{
	return pkb.follows_manager_.GetAllPredecessorStmtsFromStmt(stmt);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManager::GetAllFollowsTRelations()
{
	return pkb.follows_manager_.GetAllFollowsTRelations();
}

// APIs related to Uses relation
bool ReadPKBManager::CheckUses(StmtNum stmt_num, Variable var)
{
	return pkb.uses_manager_.CheckUses(stmt_num, var);
}

bool ReadPKBManager::CheckUses(Procedure proc_name, Variable var)
{
	return pkb.uses_manager_.CheckUses(proc_name, var);
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ReadPKBManager::GetAllSVUses()
{
	return pkb.uses_manager_.GetAllSVUses();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllUsesStatements()
{
	return pkb.uses_manager_.GetAllStatements();
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> ReadPKBManager::GetAllPVUses()
{
	return pkb.uses_manager_.GetAllPVUses();
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllUsesProcedures()
{
	return pkb.uses_manager_.GetAllProcedures();
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetUsesVarByStmtNum(StmtNum stmt_num)
{
	return pkb.uses_manager_.GetVarByStmtNum(stmt_num);
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetUsesVarByProcName(Procedure proc_name)
{
	return pkb.uses_manager_.GetVarByProcName(proc_name);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetUsesStmtNumByVar(Variable var)
{
	return pkb.uses_manager_.GetStmtNumByVar(var);
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetUsesProcNameByVar(Variable var)
{
	return pkb.uses_manager_.GetProcNameByVar(var);
}


// APIs related to Modifies relation
bool ReadPKBManager::CheckModifies(StmtNum stmt_num, Variable var)
{
	return pkb.modifies_manager_.CheckModifies(stmt_num, var);
}

bool ReadPKBManager::CheckModifies(Procedure proc_name, Variable var)
{
	return pkb.modifies_manager_.CheckModifies(proc_name, var);
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ReadPKBManager::GetAllSVModifies()
{
	return pkb.modifies_manager_.GetAllSVModifies();
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetAllModifiesStatements()
{
	return pkb.modifies_manager_.GetAllStatements();
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> ReadPKBManager::GetAllPVModifies()
{
	return pkb.modifies_manager_.GetAllPVModifies();
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetAllModifiesProcedures()
{
	return pkb.modifies_manager_.GetAllProcedures();
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetModifiesVarByStmtNum(StmtNum stmt_num)
{
	return pkb.modifies_manager_.GetVarByStmtNum(stmt_num);
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManager::GetModifiesVarByProcName(Procedure proc_name)
{
	return pkb.modifies_manager_.GetVarByProcName(proc_name);
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManager::GetModifiesStmtNumByVar(Variable var)
{
	return pkb.modifies_manager_.GetStmtNumByVar(var);
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManager::GetModifiesProcNameByVar(Variable var)
{
	return pkb.modifies_manager_.GetProcNameByVar(var);
}