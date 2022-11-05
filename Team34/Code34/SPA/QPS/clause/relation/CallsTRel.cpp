#include "CallsTRel.h"

Priority CallsTRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kCallsTRel, CountSynonyms());
}