#include "Query.h"

std::shared_ptr<std::vector<Rel>> Query::GetRelations()
{
	return relations_;
}
