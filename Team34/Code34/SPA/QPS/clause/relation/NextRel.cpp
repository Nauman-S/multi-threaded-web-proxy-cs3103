#include "NextRel.h"

Priority NextRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kNextRel, CountSynonyms());
}