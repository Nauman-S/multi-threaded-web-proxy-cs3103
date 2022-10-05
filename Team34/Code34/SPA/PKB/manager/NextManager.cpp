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

std::shared_ptr<std::unordered_set<StmtNum>> NextManager::GetNextStmtsFromStmt(StmtNum stmt)
{
	return next_store_.GetRHSByLHS(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> NextManager::GetPrevStmtsFromStmt(StmtNum stmt)
{
	return next_store_.GetLHSByRHS(stmt);
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

bool NextManager::CheckNextT(StmtNum prev, StmtNum next)
{
	return next_store_.CheckTransitiveRelation(prev, next);
}

std::shared_ptr<std::unordered_set<StmtNum>> NextManager::GetAllNextStmtsFromStmt(StmtNum stmt)
{
	return next_store_.GetAllTransitiveRHS(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> NextManager::GetAllPrevStmtsFromStmt(StmtNum stmt)
{
	return next_store_.GetAllTransitiveLHS(stmt);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> NextManager::GetAllNextTRelations()
{
	return next_store_.GetAllTransitiveRelations();
}