#pragma once

#include <memory>

#include "Table.h"
#include "EmptyTable.h"
#include "WildcardTable.h"
#include "../ResWrapper.h"

class TableFactory {
public:
    static std::shared_ptr<Table> CreateTable(std::shared_ptr<ResWrapper> res_wrapper) {
        if (res_wrapper->GetResType() == ResType::kBool && res_wrapper->IsValid()) {
            return std::make_shared<WildcardTable>();
        } else if (res_wrapper->GetResType() == ResType::kBool && !res_wrapper->IsValid()) {
            return std::make_shared<EmptyTable>();
        } else if (res_wrapper->GetResType() == ResType::kSet) {
            return std::make_shared<Table>(res_wrapper->GetSet());
        } else if (res_wrapper->GetResType() == ResType::kTable) {
            return std::make_shared<Table>(res_wrapper->GetTable());
        } else {
            return std::make_shared<EmptyTable>();
        }
    }
};
