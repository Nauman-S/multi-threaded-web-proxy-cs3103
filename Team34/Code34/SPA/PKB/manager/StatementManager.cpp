#include "StatementManager.h"

std::unordered_map<RefType, std::unordered_set<StmtNum>> StatementManager::type_to_stmt_map_;
std::unordered_map<StmtNum, RefType> StatementManager::stmt_to_type_map_;
std::unordered_set<StmtNum> StatementManager::statements_;

void StatementManager::AddStatement(StmtNum stmt_num, RefType type)
{
	assert(type != RefType::kConstRef || type != RefType::kVarRef);
	// add some defensive checks in the future to ensure that statement has not been added
	type_to_stmt_map_[type].insert(stmt_num);
	stmt_to_type_map_[stmt_num] = type;
	statements_.insert(stmt_num);
}

bool StatementManager::IsStatement(StmtNum stmt_num)
{
	return stmt_to_type_map_.find(stmt_num) != stmt_to_type_map_.end();
}

RefType StatementManager::GetStatementType(StmtNum stmt_num)
{
	auto iter = stmt_to_type_map_.find(stmt_num);
	if (iter == stmt_to_type_map_.end())
	{
		// statement number key not found, throw some error
	}
	return stmt_to_type_map_[stmt_num];
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetStatementsByType(RefType type)
{
	auto iter = type_to_stmt_map_.find(type);
	if (iter == type_to_stmt_map_.end())
	{
		return std::make_shared<std::unordered_set<StmtNum>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<StmtNum>>(type_to_stmt_map_[type]);
	}
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetAllStatements()
{
	return std::make_shared<std::unordered_set<StmtNum>>(statements_);
}