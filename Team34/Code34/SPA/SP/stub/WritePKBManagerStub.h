#pragma once

#include <set>

#include "../../PKB/WritePKBManager.h"
#include "../../Utils/type/TypeDef.h"

class WritePKBManagerStub: public WritePKBManager {
public:
	void SetCodeBlock(StmtNum, StmtNum);
	bool CheckCodeBlockSet(StmtNum, StmtNum);

	void SetOptimisedCFGEdge(StmtNum, StmtNum);
	bool CheckOptimisedEdgeSet(StmtNum, StmtNum);

	void ClearAll();

private:
	std::set<std::pair<StmtNum, StmtNum>> set_code_blocks_;
	std::set<std::pair<StmtNum, StmtNum>> set_optimised_edges;
};