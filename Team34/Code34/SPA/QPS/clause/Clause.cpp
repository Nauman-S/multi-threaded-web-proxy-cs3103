#include "Clause.h"

#include <memory>
#include <vector>
#include <string>
#include <cstdarg>

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;

std::shared_ptr<std::vector<std::string>> Clause::GetSynonyms(vector<shared_ptr<Ref>>& refs) {
    auto res = make_shared<vector<string>>();
    for (auto& ref : refs) {
        if (ref->GetValType() == ValType::kSynonym) {
            res->push_back(ref->GetName());
        }
    }

    return res;
}

int Clause::CountSynonyms(std::vector<shared_ptr<Ref>>& refs) {
    int count = 0;
    for (auto& ref : refs) {
        if (ref->GetValType() == ValType::kSynonym) {
            count += 1;
        }
    }

    return count;
}