#pragma once

#include "ManyToManyTransitiveRelationStore.h"
#include "../../../Utils/type/TypeDef.h"

class NextRelationStore : public ManyToManyTransitiveRelationStore<StmtNum>
{
public:
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllTransitiveRelations();
private:
	void PopulateNextTPairs(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> all_transitive_relations,
		StmtNum lhs, std::shared_ptr<std::unordered_set<StmtNum>> all_rhs);
};
