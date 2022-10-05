#pragma once

#include "ManyToManyTransitiveRelationStore.h"
#include "../../../Utils/type/TypeDef.h"

class NextRelationStore : public ManyToManyTransitiveRelationStore<StmtNum>
{
public:
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllTransitiveRelations();
	void SetCFGEdge(std::shared_ptr<std::pair<StmtNum, StmtNum>> prev_node, std::shared_ptr<std::pair<StmtNum, StmtNum>> next_node);
private:
	std::unordered_map<std::shared_ptr<std::pair<StmtNum, StmtNum>>, std::unordered_set<std::shared_ptr<std::pair<StmtNum, StmtNum>>>> cfg_;
};
