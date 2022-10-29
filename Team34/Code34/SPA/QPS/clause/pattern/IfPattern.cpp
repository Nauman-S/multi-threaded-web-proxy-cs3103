#include "IfPattern.h"

#include <memory>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;


int IfPattern::CountSynonyms()
{
    vector<shared_ptr<Ref>> args = { if_ref_, var_ref_ };
    return Clause::CountSynonyms(args);
}

Priority IfPattern::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kIfPattern, CountSynonyms());
}

std::shared_ptr<std::vector<std::string>> IfPattern::GetSynonyms()
{
    vector<shared_ptr<Ref>> args = { if_ref_, var_ref_ };
    return Clause::GetSynonyms(args);
}
