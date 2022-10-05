#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../store/OneToManyRelation/ParentRelationStore.h"
#include "../../Utils/type/TypeDef.h"

class ParentManager
{
public:
	// Parent Relation methods
	void SetParent(StmtNum parent, StmtNum child);
	bool CheckParent(StmtNum parent, StmtNum child);
	bool IsEmpty();
	std::shared_ptr<std::unordered_set<StmtNum>> GetChildrenFromStmt(StmtNum parent);
	std::shared_ptr<std::unordered_set<StmtNum>> GetParentFromStmt(StmtNum child);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllParents();
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildren();
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentRelations();
	
	// Parent* Relation methods
	void SetParentT(StmtNum parent, StmtNum child);
	bool CheckParentT(StmtNum parent, StmtNum child);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildrenFromStmt(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllParentsFromStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentTRelations();
private:
	ParentRelationStore<StmtNum> parent_store_;
};