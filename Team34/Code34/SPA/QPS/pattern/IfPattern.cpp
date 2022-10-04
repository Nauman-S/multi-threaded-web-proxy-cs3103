#include "IfPattern.h"

int IfPattern::CountSynonyms()
{
    int res = 0;
    if (if_ref_->GetValType() == ValType::kSynonym) {
        res += 1;
    }
    if (var_ref_->GetValType() == ValType::kSynonym) {
        res += 1;
    }

    return res;
}
