#include "AssignPattern.h"

#include <memory>
#include <string>
#include <vector>

#include "../../optimization/PriorityManager.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;


int AssignPattern::CountSynonyms()
{
    vector<shared_ptr<Ref>> args = { assign_ref_, var_ref_ };
    return Clause::CountSynonyms(args);
}

Priority AssignPattern::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kAssignPattern, CountSynonyms());
}

std::shared_ptr<std::vector<std::string>> AssignPattern::GetSynonyms()
{
    vector<shared_ptr<Ref>> args = { assign_ref_, var_ref_ };
    return Clause::GetSynonyms(args);
}
