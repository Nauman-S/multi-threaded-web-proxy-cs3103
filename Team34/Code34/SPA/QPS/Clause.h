#pragma once

#include <memory>

#include "ClauseType.h"
#include "PriorityManager.h"
#include "reference/Ref.h"
#include "query_result/ResWrapper.h"
#include "../Utils/type/TypeDef.h"
class DataRetriever;


class Clause {
protected:
    std::shared_ptr<std::vector<std::string>> GetSynonyms(std::vector<std::shared_ptr<Ref>>& refs);

    int CountSynonyms(std::vector<std::shared_ptr<Ref>>& refs);

public:

    virtual std::shared_ptr<ResWrapper> GetMatch(DataRetriever& retriever) = 0;

    virtual std::shared_ptr<std::vector<std::string>> GetSynonyms() = 0;

    virtual int CountSynonyms() = 0;

    virtual Priority GetPriority(PriorityManager& pm) = 0;

};

