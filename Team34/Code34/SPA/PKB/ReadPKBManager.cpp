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

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> ReadPKBManager::GetAllPVUses()
{
	return pkb.uses_manager_.GetAllPVUses();
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
bool ReadPKBManager::CheckModifies(int stmt_num, std::string var)
{
	return pkb.modifies_manager_.CheckModifies(stmt_num, var);
}

bool ReadPKBManager::CheckModifies(std::string proc_name, std::string var)
{
	return pkb.modifies_manager_.CheckModifies(proc_name, var);
}

const std::vector<std::pair<int, std::string>>& ReadPKBManager::GetAllSVModifies()
{
	return pkb.modifies_manager_.GetAllSVModifies();
}

const std::vector<std::pair<std::string, std::string>>& ReadPKBManager::GetAllPVModifies()
{
	return pkb.modifies_manager_.GetAllPVModifies();
}

std::unordered_set<std::string> ReadPKBManager::GetModifiesVarByStmtNum(int stmt_num)
{
	return pkb.modifies_manager_.GetVarByStmtNum(stmt_num);
}

std::unordered_set<std::string> ReadPKBManager::GetModifiesVarByProcName(std::string proc_name)
{
	return pkb.modifies_manager_.GetVarByProcName(proc_name);
}

std::unordered_set<int> ReadPKBManager::GetModifiesStmtNumByVar(std::string var)
{
	return pkb.modifies_manager_.GetStmtNumByVar(var);
}

std::unordered_set<std::string> ReadPKBManager::GetModifiesProcNameByVar(std::string var)
{
	return pkb.modifies_manager_.GetProcNameByVar(var);
}