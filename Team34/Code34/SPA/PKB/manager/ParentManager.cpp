# include "ParentManager.h"

// Parent Relation methods
void ParentManager::SetParent(StmtNum parent, StmtNum child)
{
	parent_store_.SetRelation(parent, child);
}

bool ParentManager::CheckParent(StmtNum parent, StmtNum child)
{
	return parent_store_.CheckRelation(parent, child);
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetChildrenFromStmt(StmtNum parent)
{
	return parent_store_.GetMany(parent);
}

StmtNum ParentManager::GetParentFromStmt(StmtNum child)
{
	return parent_store_.GetOne(child);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ParentManager::GetAllParentRelations()
{
	return parent_store_.GetAllRelations();
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetAllParents()
{
	return parent_store_.GetAllLHS();
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetAllChildren()
{
	return parent_store_.GetAllRHS();
}

bool ParentManager::IsEmpty()
{
	return parent_store_.IsEmpty();
}

// Parent* Relation methods
void ParentManager::SetParentT(StmtNum parent, StmtNum child)
{
	parent_store_.SetTransitiveRelation(parent, child);
}

bool ParentManager::CheckParentT(StmtNum parent, StmtNum child)
{
	return parent_store_.CheckTransitiveRelation(parent, child);
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetAllChildrenFromStmt(StmtNum stmt)
{
	return parent_store_.GetAllTransitiveMany(stmt);
}

std::shared_ptr<std::unordered_set<StmtNum>> ParentManager::GetAllParentsFromStmt(StmtNum stmt)
{
	return parent_store_.GetAllTransitiveOne(stmt);
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ParentManager::GetAllParentTRelations()
{
	return parent_store_.GetAllTransitiveRelations();
}