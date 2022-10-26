#include "With.h"

#include <memory>
#include <string>
#include <vector>

#include "../../DataRetriever.h"
#include "../../optimization/PriorityManager.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;


std::shared_ptr<ResWrapper> With::GetMatch(DataRetriever& retriever)
{
	return retriever.retrieve(*this);
}

int With::CountSynonyms()
{
    vector<shared_ptr<Ref>> args = { lhs_ref_ptr_, rhs_ref_ptr_ };
    return Clause::CountSynonyms(args);
}

Priority With::GetPriority(PriorityManager& pm) {
    return pm.GetClausePriority(ClauseType::kWith);
}

std::shared_ptr<std::vector<std::string>> With::GetSynonyms()
{
    vector<shared_ptr<Ref>> args = { lhs_ref_ptr_, rhs_ref_ptr_ };
    return Clause::GetSynonyms(args);
}
