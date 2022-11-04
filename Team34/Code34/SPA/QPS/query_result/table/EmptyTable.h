#pragma once

#include "Table.h"

#include "memory"

class EmptyTable
    : public Table {
public:
    bool IsEmpty() override { return true; };

    std::shared_ptr<Table> Join(std::shared_ptr<Table> that) override {
        return std::shared_ptr<EmptyTable>(this);
    }
};