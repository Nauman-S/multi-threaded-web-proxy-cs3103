# include "ParentManager.h"

// Parent Relation methods
void ParentManager::SetParent(StmtNum child, StmtNum parent)
{

}
bool ParentManager::CheckParent(StmtNum child, StmtNum parent)
{
	return false;
}

StmtNum ParentManager::GetChild(StmtNum parent)
{
	return StmtNum();
}

StmtNum ParentManager::GetParent(StmtNum child)
{
	return StmtNum();
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ParentManager::GetAllParentRelations()
{
	return std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>>();
}

// Parent* Relation methods
void ParentManager::SetParentS(StmtNum child, StmtNum parent)
{
}

bool ParentManager::CheckParentS(StmtNum child, StmtNum parent)
{
	return false;
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetAllChildren(StmtNum parent)
{
	return std::shared_ptr<std::unordered_set<StmtNum>>();
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetAllParents(StmtNum parent)
{
	return std::shared_ptr<std::unordered_set<StmtNum>>();
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ParentManager::GetAllParentSRelations()
{
	return std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>>();
}

