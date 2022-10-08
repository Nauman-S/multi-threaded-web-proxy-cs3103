#include "StatementManager.h"

void StatementManager::AddStatement(StmtNum stmt_num, RefType type)
{
	assert(type != RefType::kConstRef && type != RefType::kVarRef);
	statement_store_.SetRelation(stmt_num, type);
	statements_.insert(stmt_num);
}

void StatementManager::AddCallsStatement(Procedure proc, StmtNum stmt_num)
{
	calls_statements_[proc].insert(stmt_num);
}

void StatementManager::AddPrintStatement(Variable var, StmtNum stmt_num)
{
	print_statements_[var].insert(stmt_num);
}

void StatementManager::AddReadStatement(Variable var, StmtNum stmt_num)
{
	read_statements_[var].insert(stmt_num);
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

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetCallsStatementFromProcedure(Procedure proc)
{
	if (calls_statements_.find(proc) == calls_statements_.end())
	{
		return std::make_shared<std::unordered_set<StmtNum>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<StmtNum>>(calls_statements_[proc]);
	}
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetPrintStatementFromVariable(Variable var)
{
	if (print_statements_.find(var) == print_statements_.end())
	{
		return std::make_shared<std::unordered_set<StmtNum>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<StmtNum>>(print_statements_[var]);
	}
}

std::shared_ptr<std::unordered_set<StmtNum>> StatementManager::GetReadStatementFromVariable(Variable var)
{
	if (read_statements_.find(var) == read_statements_.end())
	{
		return std::make_shared<std::unordered_set<StmtNum>>();
	}
	else
	{
		return std::make_shared<std::unordered_set<StmtNum>>(read_statements_[var]);
	}
}
