#include "StatementManager.h"

void StatementManager::AddStatement(StmtNum stmt_num, RefType type)
{
	assert(type != RefType::kConstRef && type != RefType::kVarRef);
	statement_store_.SetRelation(stmt_num, type);
	statements_.insert(stmt_num);
}

std::shared_ptr<RefType> StatementManager::GetStatementType(StmtNum stmt_num)
{
	return statement_store_.GetOne(stmt_num);
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetStatementsByType(RefType type)
{
	return statement_store_.GetMany(type);
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetAllStatements()
{
	return std::make_shared<std::unordered_set<StmtNum>>(statements_);
}