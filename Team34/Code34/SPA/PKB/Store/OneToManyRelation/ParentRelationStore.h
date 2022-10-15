#pragma once

#include "OneToManyTransitiveRelationStore.h"
#include "../../../Utils/type/TypeDef.h"

class ParentRelationStore : public OneToManyTransitiveRelationStore<StmtNum>
{
public:
	void SetTransitiveRelation(StmtNum left, StmtNum right);
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllTransitiveRelations();
	void Clear();
private:
	std::vector<std::pair<StmtNum, StmtNum>> all_transitive_relations_;
};
