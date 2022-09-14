#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../store/OneToManyTransitiveRelationStore.h"
#include "../../Utils/type/TypeDef.h"

class ParentManager
{
public:
	// Parent Relation methods
	void SetParent(StmtNum parent, StmtNum child);
	bool CheckParent(StmtNum parent, StmtNum child);
	std::shared_ptr<std::unordered_set<StmtNum>> GetChildrenFromStmt(StmtNum parent);
	StmtNum GetParentFromStmt(StmtNum child);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentRelations();
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllParents();
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildren();
	bool IsEmpty();
	
	// Parent* Relation methods
	void SetParentT(StmtNum parent, StmtNum child);
	bool CheckParentT(StmtNum parent, StmtNum child);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildrenFromStmt(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllParentsFromStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentTRelations();
private:
	OneToManyTransitiveRelationStore<StmtNum> parent_store_;
};