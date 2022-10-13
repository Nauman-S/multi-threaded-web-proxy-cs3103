#pragma once

#include <cassert>
#include <memory>
#include <unordered_set>
#include <vector>

#include "../store/OneToOneRelation/FollowsRelationStore.h"
#include "../../Utils/type/TypeDef.h"

class FollowsManager
{
public:
	// Follows Relation methods
	void SetFollows(StmtNum left, StmtNum right);
	bool CheckFollows(StmtNum left, StmtNum right);
	bool IsEmpty();
	std::shared_ptr<std::unordered_set<StmtNum>> GetSuccessorStmtFromStmt(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetPredecessorStmtFromStmt(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmts();
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmts();
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsRelations();

	// Follows* Relation methods
	void SetFollowsT(StmtNum left, StmtNum right);
	bool CheckFollowsT(StmtNum left, StmtNum right);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllSuccessorStmtsFromStmt(StmtNum stmt);
	std::shared_ptr<std::unordered_set<StmtNum>> GetAllPredecessorStmtsFromStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsTRelations();

	void Clear();
private:
	FollowsRelationStore follows_store_;
};