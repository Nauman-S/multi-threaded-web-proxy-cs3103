#pragma once

#include <unordered_map>

#include "clause/ClauseType.h"
#include "../Utils/type/TypeDef.h"

class PriorityManager {
private:
    std::unordered_map<ClauseType, Priority> priority_map_ = {
        // SMALLER priority number has HIGHER priority (should just sort ascendingly)
        {ClauseType::kParentRel, 0},
        {ClauseType::kFollowsRel, 0},
        {ClauseType::kCallsRel, 0},
        {ClauseType::kNextRel, 0},
        {ClauseType::kAffectsRel, 0},

        {ClauseType::kModifiesPRel, 1},
        {ClauseType::kUsesPRel, 1},

        {ClauseType::kModifiesSRel, 2},
        {ClauseType::kUsesSRel, 2},

        {ClauseType::kAssignPattern, 3},
        {ClauseType::kIfPattern, 3},
        {ClauseType::kWhilePattern, 3},

        {ClauseType::kWith, 4},

        {ClauseType::kParentTRel, 5},
        {ClauseType::kFollowsTRel, 5},
        {ClauseType::kCallsTRel, 5},
        {ClauseType::kNextTRel, 5},
        {ClauseType::kAffectsTRel, 5},
    };

public:
    Priority GetClausePriority(ClauseType type) { return priority_map_[type]; }

};