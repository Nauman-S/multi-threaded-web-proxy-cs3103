#include "FollowsManager.h"

// Follows Relation methods
void FollowsManager::SetFollows(StmtNum left, StmtNum right)
{
    follows_store_.SetRelation(left, right);
}

bool FollowsManager::CheckFollows(StmtNum left, StmtNum right)
{
    return follows_store_.CheckRelation(left, right);
}

StmtNum FollowsManager::GetSuccessorStmt(StmtNum stmt)
{
    return follows_store_.GetRHSByLHS(stmt);
}

StmtNum FollowsManager::GetPredecessorStmt(StmtNum stmt)
{
    return follows_store_.GetLHSByRHS(stmt);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> FollowsManager::GetAllFollowsRelations()
{
    return follows_store_.GetAllRelations();
}

std::shared_ptr<std::unordered_set<StmtNum>> FollowsManager::GetAllPredecessorStmts()
{
    return follows_store_.GetAllLHS();
}

std::shared_ptr<std::unordered_set<StmtNum>> FollowsManager::GetAllSuccessorStmts()
{
    return follows_store_.GetAllRHS();
}

// Follows* Relation methods
void FollowsManager::SetFollowsT(StmtNum left, StmtNum right)
{
    follows_store_.SetTransitiveRelation(left, right);
}

bool FollowsManager::CheckFollowsT(StmtNum left, StmtNum right)
{
    return follows_store_.CheckTransistiveRelation(left, right);
}

std::shared_ptr<std::vector<StmtNum>> FollowsManager::GetAllSuccessorStmt(StmtNum stmt)
{
    return follows_store_.GetAllRHSByLHS(stmt);
}

std::shared_ptr<std::vector<StmtNum>> FollowsManager::GetAllPredecessorStmt(StmtNum stmt)
{
    return follows_store_.GetAllLHSByRHS(stmt);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> FollowsManager::GetAllFollowsTRelations()
{
    return follows_store_.GetAllTransitiveRelations();
}
