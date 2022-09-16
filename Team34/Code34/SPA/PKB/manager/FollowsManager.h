#pragma once

#include <cassert>
#include <memory>
#include <unordered_set>
#include <vector>

#include "../store/OneToOneTransitiveRelationStore.h"
#include "../../Utils/type/TypeDef.h"

class FollowsManager
{
public:
	// Follows Relation methods
	void SetFollows(StmtNum left, StmtNum right);
	bool CheckFollows(StmtNum left, StmtNum right);
	StmtNum GetSuccessorStmtFromStmt(StmtNum stmt);
	StmtNum GetPredecessorStmtFromStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsRelations();
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmts();
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmts();
	bool IsEmpty();

	// Follows* Relation methods
	void SetFollowsT(StmtNum left, StmtNum right);
	bool CheckFollowsT(StmtNum left, StmtNum right);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmtsFromStmt(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmtsFromStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsTRelations();
private:
	OneToOneTransitiveRelationStore<StmtNum> follows_store_;
};