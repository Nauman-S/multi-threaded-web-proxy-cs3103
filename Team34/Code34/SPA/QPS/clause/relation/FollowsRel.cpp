#include "FollowsRel.h"

Priority FollowsRel::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kFollowsRel, CountSynonyms());
}
