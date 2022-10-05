#include "ModifiesPRel.h"

Priority ModifiesPRel::GetPriority(PriorityManager pm) { 
	return pm.GetClausePriority(ClauseType::kModifiesPRel); 
}