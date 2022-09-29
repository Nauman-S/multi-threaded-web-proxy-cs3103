#include "NextManager.h"

void NextManager::SetNext(StmtNum prev, StmtNum next)
{
	next_store_.SetRelation(prev, next);
}

bool NextManager::CheckNext(StmtNum prev, StmtNum next)
{
	return next_store_.CheckRelation(prev, next);
}

bool NextManager::IsEmpty()
{
	return next_store_.IsEmpty();
}

std::shared_ptr<std::unordered_set<StmtNum>> NextManager::GetNextStmtFromStmt(StmtNum stmt)
{
	return std::shared_ptr<std::unordered_set<StmtNum>>();
}

std::shared_ptr<std::unordered_set<StmtNum>> NextManager::GetPrevStmtsFromStmt(StmtNum stmt)
{
	return std::shared_ptr<std::unordered_set<StmtNum>>();
}


std::shared_ptr<std::unordered_set<StmtNum>> NextManager::GetAllNextStmts()
{
	return next_store_.GetAllRHS();
}

std::shared_ptr<std::unordered_set<StmtNum>> NextManager::GetAllPrevStmts()
{
	return next_store_.GetAllLHS();
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> NextManager::GetAllNextRelations()
{
	return next_store_.GetAllRelations();
}

