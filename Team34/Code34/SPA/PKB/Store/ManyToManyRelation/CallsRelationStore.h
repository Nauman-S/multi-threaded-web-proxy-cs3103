#pragma once

#include "ManyToManyTransitiveRelationStore.h"
#include "../../../Utils/type/TypeDef.h"

class CallsRelationStore : public ManyToManyTransitiveRelationStore<Procedure>
{
public:
	void SetTransitiveRelation(Procedure left, Procedure right);
	std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> GetAllTransitiveRelations();
private:
	std::vector<std::pair<Procedure, Procedure>> all_transitive_relations_;
};
