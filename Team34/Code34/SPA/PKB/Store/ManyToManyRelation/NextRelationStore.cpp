#include "NextRelationStore.h"

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> NextRelationStore::GetAllTransitiveRelations()
{
	return std::make_shared<std::vector<std::pair<StmtNum, StmtNum>>>();
}
