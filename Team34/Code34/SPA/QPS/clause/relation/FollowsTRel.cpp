#include "FollowsTRel.h"

Priority FollowsTRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kFollowsTRel, CountSynonyms());
}