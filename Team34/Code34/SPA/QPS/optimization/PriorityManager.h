#pragma once

#include <unordered_map>
#include <utility>

#include "../clause/ClauseType.h"
#include "../clause/Clause.h"
#include "../../Utils/type/TypeDef.h"

class PriorityManager {
private:
    // Refers to https://stackoverflow.com/questions/32685540/why-cant-i-compile-an-unordered-map-with-a-pair-as-key
    struct pair_hash {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2>& pair) const {
            auto h1 = std::hash<T1>{}(pair.first);
            auto h2 = std::hash<T2>{}(pair.second);
            return h1 ^ h2;
        }
    };

    // The map maps (clause type, number of synonym) to a priority number
    // The smaller number represents higher priority
    // The priority is determined by the estimated size of the result and time taken to get the result
    std::unordered_map<std::pair<ClauseType, int>, Priority, pair_hash> priority_map_ = {
        // SMALLER priority number has HIGHER priority
        {std::make_pair(ClauseType::kParentRel, 1), 0},
        {std::make_pair(ClauseType::kFollowsRel, 1), 0},
        {std::make_pair(ClauseType::kCallsRel, 1), 0},
        {std::make_pair(ClauseType::kNextRel, 1), 0},
        {std::make_pair(ClauseType::kWith, 1), 0},

        {std::make_pair(ClauseType::kModifiesPRel, 1), 2},
        {std::make_pair(ClauseType::kUsesPRel, 1), 2},

        {std::make_pair(ClauseType::kModifiesSRel, 1), 3},
        {std::make_pair(ClauseType::kUsesSRel, 1), 3},
        {std::make_pair(ClauseType::kIfPattern, 1), 3},
        {std::make_pair(ClauseType::kWhilePattern, 1), 3},
        {std::make_pair(ClauseType::kAffectsRel, 1), 3},

        {std::make_pair(ClauseType::kAssignPattern, 1), 4},
        {std::make_pair(ClauseType::kParentTRel, 1), 4},

        {std::make_pair(ClauseType::kFollowsTRel, 1), 5},
        {std::make_pair(ClauseType::kCallsTRel, 1), 5},

        {std::make_pair(ClauseType::kAffectsTRel, 1), 7},
        {std::make_pair(ClauseType::kCallsRel, 2), 7},

        {std::make_pair(ClauseType::kNextTRel, 1), 8},
        {std::make_pair(ClauseType::kParentRel, 2), 8},

        {std::make_pair(ClauseType::kModifiesPRel, 2), 10},
        {std::make_pair(ClauseType::kModifiesSRel, 2), 10},
        {std::make_pair(ClauseType::kParentTRel, 2), 10},
        {std::make_pair(ClauseType::kCallsTRel, 2), 10},
        {std::make_pair(ClauseType::kFollowsRel, 2), 10},

        {std::make_pair(ClauseType::kUsesPRel, 2), 15},
        {std::make_pair(ClauseType::kUsesSRel, 2), 15},

        {std::make_pair(ClauseType::kNextRel, 2), 20},
        {std::make_pair(ClauseType::kIfPattern, 2), 20},
        {std::make_pair(ClauseType::kWhilePattern, 2), 20},

        {std::make_pair(ClauseType::kWith, 2), 30},
        {std::make_pair(ClauseType::kAssignPattern, 2), 30},

        {std::make_pair(ClauseType::kAffectsRel, 2), 50},
        {std::make_pair(ClauseType::kNextTRel, 2), 50},

        {std::make_pair(ClauseType::kFollowsTRel, 2), 80},

        {std::make_pair(ClauseType::kAffectsTRel, 2), 100}
    };

public:
    Priority GetClausePriority(ClauseType type, int syn_num) { return priority_map_[std::make_pair(type, syn_num)]; }
};