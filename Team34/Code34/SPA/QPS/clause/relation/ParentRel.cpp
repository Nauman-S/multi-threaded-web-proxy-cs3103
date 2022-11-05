#include "ParentRel.h"

Priority ParentRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kParentRel, CountSynonyms());
}