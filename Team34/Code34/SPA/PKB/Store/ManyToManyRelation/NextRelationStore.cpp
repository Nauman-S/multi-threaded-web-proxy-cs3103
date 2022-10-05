#include "NextRelationStore.h"

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> NextRelationStore::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<StmtNum, StmtNum>>>();
}

void NextRelationStore::SetCFGEdge(std::shared_ptr<std::pair<StmtNum, StmtNum>> prev_node, std::shared_ptr<std::pair<StmtNum, StmtNum>> next_node)
{
	cfg_[prev_node].insert(next_node);
}
