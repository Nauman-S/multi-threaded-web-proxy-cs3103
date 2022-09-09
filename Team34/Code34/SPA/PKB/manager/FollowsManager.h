#pragma once

#include <cassert>
#include <memory>
#include <vector>

#include "../store/OneToOneTransitiveRelationStore.h"
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
	void SetFollowsS(StmtNum left, StmtNum right);
	bool CheckFollowsS(StmtNum left, StmtNum right);
	std::shared_ptr<std::vector<StmtNum>> GetAllSuccessorStmt(StmtNum stmt);
	std::shared_ptr<std::vector<StmtNum>> GetAllPredecessorStmt(StmtNum stmt);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllFollowsSRelations();

private:
	OneToOneTransitiveRelationStore<StmtNum> follows_store_;
};