#include "ModifiesSRel.h"

Priority ModifiesSRel::GetPriority(PriorityManager& pm) { 
	return pm.GetClausePriority(ClauseType::kModifiesSRel); 
}
