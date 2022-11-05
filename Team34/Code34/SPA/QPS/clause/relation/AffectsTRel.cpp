#include "AffectsTRel.h"

Priority AffectsTRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kAffectsTRel, CountSynonyms());
}