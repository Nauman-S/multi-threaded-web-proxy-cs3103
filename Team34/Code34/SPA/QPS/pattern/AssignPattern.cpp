#include "AssignPattern.h"
#include "../DataRetriever.h"

int AssignPattern::CountSynonyms()
{
    int res = 0;
    if (assign_ref_->GetValType() == ValType::kSynonym) {
        res += 1;
    }
    if (var_ref_->GetValType() == ValType::kSynonym) {
        res += 1;
    }

    return res;
}
