#pragma once

#include <cassert>
#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../store/ManyToManyRelation/NextRelationStore.h"
#include "../../Utils/type/TypeDef.h"
#include "../../Utils/type/RefType.h"

class NextManager
{
public:
	// Next Relation Methods
	void SetNext(StmtNum prev, StmtNum next);
	bool CheckNext(StmtNum prev, StmtNum next);
	bool IsEmpty();
	std::shared_ptr<std::unordered_set<StmtNum>> GetNextStmtsFromStmt(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetPrevStmtsFromStmt(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllNextStmts();
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllPrevStmts();
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllNextRelations();

	// Next* Relation methods
	void SetCFGEdge(std::shared_ptr<std::pair<StmtNum, StmtNum>> prev_node, std::shared_ptr<std::pair<StmtNum, StmtNum>> next_node);
	bool CheckNextT(StmtNum parent, StmtNum child);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllNextStmtsFromStmt(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllPrevStmtsFromStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllNextTRelations();
private:
	NextRelationStore next_store_;
};