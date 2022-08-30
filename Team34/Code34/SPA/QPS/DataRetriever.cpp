#include <memory>

#include "DataRetriever.h"

std::shared_ptr<QueryResult> DataRetriever::retrieve(StmtVarRel rel)
{
    auto [lhs_type, rhs_type] = rel.ValTypes();
    
    auto res = std::make_shared<QueryResult>();
    if (lhs_type == ValType::kLineNum && rhs_type == ValType::kVarName) {
        bool ok = CheckSVRel(rel);
    }
    else if (lhs_type == ValType::kLineNum) {
        // rhs_type is kSynonym or kWildcard
        auto& domain = GetVarByStmt(rel);
        string rhs_syn = rel.RhsValue();
        res->SetDomain(rhs_syn, domain);
    }
    else if (rhs_type == ValType::kVarName) {
        // lhs_type is kSynonym or kWildcard
        auto& domain = GetStmtByVar(rel);
        string lhs_syn = rel.LhsValue();
        res->SetDomain(lhs_syn, domain);
    }
    else {
        // Both are kSynonym or kWildcard
        auto pr = std::make_pair(rel.LhsValue(), rel.RhsValue());
    }

    return res;
}
