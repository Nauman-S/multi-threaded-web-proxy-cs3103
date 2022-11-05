#include "UsesSRel.h"

Priority UsesSRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kUsesSRel, CountSynonyms());
}