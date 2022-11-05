#include "CallsRel.h"

Priority CallsRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kCallsRel, CountSynonyms());
}