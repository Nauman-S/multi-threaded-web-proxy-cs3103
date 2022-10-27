#include "NextTRel.h"

Priority NextTRel::GetPriority(PriorityManager& pm) {
	return pm.GetClausePriority(ClauseType::kNextTRel, CountSynonyms());
}