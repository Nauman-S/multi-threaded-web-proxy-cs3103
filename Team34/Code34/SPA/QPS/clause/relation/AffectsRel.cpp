#include "AffectsRel.h"

Priority AffectsRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kAffectsRel, CountSynonyms());
}