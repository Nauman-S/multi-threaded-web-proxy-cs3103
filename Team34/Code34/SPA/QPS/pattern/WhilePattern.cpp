#include "WhilePattern.h"

int WhilePattern::CountSynonyms()
{
    int res = 0;
    if (while_ref_->GetValType() == ValType::kSynonym) {
        res += 1;
    }
    if (var_ref_->GetValType() == ValType::kSynonym) {
        res += 1;
    }

    return res;
}

Priority WhilePattern::GetPriority(PriorityManager pm) {
    return pm.GetClausePriority(ClauseType::kWhilePattern);
}