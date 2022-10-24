#include "ResTableCache.h"

#include <unordered_map>
#include <memory>
#include <vector>
#include <string>

using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::string;
using std::unordered_map;

bool ResTableCache::HasCache(ClauseType type) {
    return cache_map_.find(type) != cache_map_.end();
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>> ResTableCache::GetCachedTable(ClauseType type) {
    return cache_map_.find(type)->second;
}

void ResTableCache::PutCachedTable(ClauseType type, std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table) {
    cache_map_.insert_or_assign(type, table);
}
