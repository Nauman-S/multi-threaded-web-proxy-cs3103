#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


#include "../clause/ClauseType.h"


class ResTableCache {
protected:
    std::unordered_map<ClauseType, std::shared_ptr<std::vector<std::pair<std::string, std::string>>>> cache_map_;

public:
    bool HasCache(ClauseType type);

    std::shared_ptr<std::vector<std::pair<std::string, std::string>>> GetCachedTable(ClauseType type);

    void PutCachedTable(ClauseType type, std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table);
};

