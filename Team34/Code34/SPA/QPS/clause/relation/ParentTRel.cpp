#include "ParentTRel.h"

Priority ParentTRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kParentTRel, CountSynonyms());
}