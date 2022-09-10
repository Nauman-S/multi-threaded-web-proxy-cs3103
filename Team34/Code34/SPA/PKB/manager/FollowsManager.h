#pragma once

#include <cassert>
#include <memory>
#include <vector>

#include "../store/OneToOneRelationStore.h"
#include "../../Utils/type/TypeDef.h"

class FollowsManager
{
public:
	// Follows Relation methods
	void SetFollows(StmtNum left, StmtNum right);
	bool CheckFollows(StmtNum left, StmtNum right);
	StmtNum GetSuccessorStmt(StmtNum stmt);
	StmtNum GetPredecessorStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsRelations();

	// Follows* Relation methods
	void SetFollowsT(StmtNum left, StmtNum right);
	bool CheckFollowsT(StmtNum left, StmtNum right);
	std::shared_ptr<std::vector<StmtNum>> GetAllSuccessorStmt(StmtNum stmt);
	std::shared_ptr<std::vector<StmtNum>> GetAllPredecessorStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsTRelations();

private:
	OneToOneRelationStore<StmtNum> follows_store_;
};