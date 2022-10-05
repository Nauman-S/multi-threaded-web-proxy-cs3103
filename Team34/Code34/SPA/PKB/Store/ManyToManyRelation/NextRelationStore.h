#pragma once

#include "ManyToManyTransitiveRelationStore.h"
#include "../../../Utils/type/TypeDef.h"

class NextRelationStore : public ManyToManyTransitiveRelationStore<StmtNum>
{
public:
	std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllTransitiveRelations();
};
