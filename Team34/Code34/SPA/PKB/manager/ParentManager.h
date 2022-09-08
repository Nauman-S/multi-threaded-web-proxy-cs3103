#pragma once

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../../Utils/type/TypeDef.h"

class ParentManager
{
public:
	// Parent Relation methods
	void SetParent(StmtNum child, StmtNum parent);
	bool CheckParent(StmtNum child, StmtNum parent);
	StmtNum GetChild(StmtNum parent);
	StmtNum GetParent(StmtNum child);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentRelations();
	
	// Parent* Relation methods
	void SetParentS(StmtNum child, StmtNum parent);
	bool CheckParentS(StmtNum child, StmtNum parent);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllChildren(StmtNum parent);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllParents(StmtNum parent);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllParentSRelations();

private:
	std::vector<std::pair<StmtNum, StmtNum>> all_parent_s_relations_;
	std::unordered_map<StmtNum, std::unordered_set<StmtNum>> parent_to_child_map_;
	std::unordered_map<StmtNum, StmtNum> child_to_parent_map_;
};