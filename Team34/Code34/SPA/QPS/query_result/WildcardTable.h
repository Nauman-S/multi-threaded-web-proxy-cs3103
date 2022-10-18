#pragma once

#include "Table.h"
class WildcardTable :
    public Table
{
public:
    bool IsWildcard() override { return true; };
    
    std::shared_ptr<Table> Join(std::shared_ptr<Table> that) override {
        return that;
    }

    bool IsEmpty() override { return false; };
};

