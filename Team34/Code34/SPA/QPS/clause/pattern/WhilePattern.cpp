#include "WhilePattern.h"

#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;


int WhilePattern::CountSynonyms() {
    vector<shared_ptr<Ref>> args = { while_ref_, var_ref_ };
    return Clause::CountSynonyms(args);
}

Priority WhilePattern::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kWhilePattern, CountSynonyms());
}

std::shared_ptr<std::vector<std::string>> WhilePattern::GetSynonyms() {
    vector<shared_ptr<Ref>> args = { while_ref_, var_ref_ };
    return Clause::GetSynonyms(args);
}
