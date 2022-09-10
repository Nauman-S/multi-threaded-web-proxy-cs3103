#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../store/OneToManyRelationStore.h"
#include "../../Utils/type/TypeDef.h"

class ParentManager
{
public:
	// Parent Relation methods
	void SetParent(StmtNum parent, StmtNum child);
	bool CheckParent(StmtNum parent, StmtNum child);
	std::shared_ptr<std::unordered_set<StmtNum>> GetChild(StmtNum parent);
	StmtNum GetParent(StmtNum child);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentRelations();
	
	// Parent* Relation methods
	void SetParentT(StmtNum parent, StmtNum child);
	bool CheckParentT(StmtNum parent, StmtNum child);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildren(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllParents(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentTRelations();

private:
	OneToManyRelationStore<StmtNum> parent_store_;
};