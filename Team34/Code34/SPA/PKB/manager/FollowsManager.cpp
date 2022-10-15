#include "FollowsManager.h"

// Follows Relation methods
void FollowsManager::SetFollows(StmtNum left, StmtNum right)
{
    if (left < right)
    {
        follows_store_.SetRelation(left, right);
    }
}

bool FollowsManager::CheckFollows(StmtNum left, StmtNum right)
{
    return follows_store_.CheckRelation(left, right);
}

bool FollowsManager::IsEmpty()
{
    return follows_store_.IsEmpty();
}

std::shared_ptr<std::unordered_set<StmtNum>> FollowsManager::GetSuccessorStmtFromStmt(StmtNum stmt)
{
    return follows_store_.GetRHSByLHS(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> FollowsManager::GetPredecessorStmtFromStmt(StmtNum stmt)
{
    return follows_store_.GetLHSByRHS(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> FollowsManager::GetAllPredecessorStmts()
{
    return follows_store_.GetAllLHS();
}

std::shared_ptr<std::unordered_set<StmtNum>> FollowsManager::GetAllSuccessorStmts()
{
    return follows_store_.GetAllRHS();
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> FollowsManager::GetAllFollowsRelations()
{
    return follows_store_.GetAllRelations();
}

// Follows* Relation methods
void FollowsManager::SetFollowsT(StmtNum left, StmtNum right)
{
    if (left < right)
    {
        follows_store_.SetTransitiveRelation(left, right);
    }
}

bool FollowsManager::CheckFollowsT(StmtNum left, StmtNum right)
{
    return follows_store_.CheckTransistiveRelation(left, right);
}

std::shared_ptr<std::unordered_set<StmtNum>> FollowsManager::GetAllSuccessorStmtsFromStmt(StmtNum stmt)
{
    return follows_store_.GetAllRHSByLHS(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> FollowsManager::GetAllPredecessorStmtsFromStmt(StmtNum stmt)
{
    return follows_store_.GetAllLHSByRHS(stmt);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> FollowsManager::GetAllFollowsTRelations()
{
    return follows_store_.GetAllTransitiveRelations();
}

void FollowsManager::Clear()
{
    follows_store_.Clear();
}
