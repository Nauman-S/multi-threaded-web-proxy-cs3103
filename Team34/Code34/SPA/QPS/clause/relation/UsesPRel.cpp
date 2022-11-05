#include "UsesPRel.h"

Priority UsesPRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kUsesPRel, CountSynonyms());
}