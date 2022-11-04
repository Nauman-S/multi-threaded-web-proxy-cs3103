#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>

#include "../clause/ClauseType.h"
#include "../../Utils/type/TypeDef.h"

template <typename T, typename S>
class ResTableCache {
protected:
    std::unordered_map<ClauseType, std::shared_ptr<std::vector<std::pair<T, S>>>> cache_map_;

public:
    bool HasCache(ClauseType type) {
        return cache_map_.find(type) != cache_map_.end();
    }

    std::shared_ptr<std::vector<std::pair<T, S>>> GetCachedTable(ClauseType type) {
        return cache_map_.find(type)->second;
    }

    void PutCacheTable(ClauseType type, std::shared_ptr<std::vector<std::pair<T, S>>> table) {
        cache_map_.insert_or_assign(type, table);
    }
};
