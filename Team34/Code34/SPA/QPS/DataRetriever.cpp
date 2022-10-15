#include "DataRetriever.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../PKB/ReadPKBManager.h"
#include "../PKB/manager/UsesManager.h"
#include "../Utils/type/TypeDef.h"
#include "ClauseType.h"
#include "pattern/AssignPattern.h"
#include "pattern/IfPattern.h"
#include "pattern/Pattern.h"
#include "pattern/WhilePattern.h"
#include "reference/ValType.h"
#include "relation/AffectsRel.h"
#include "relation/AffectsTRel.h"
#include "relation/CallsRel.h"
#include "relation/CallsTRel.h"
#include "relation/FollowsRel.h"
#include "relation/FollowsTRel.h"
#include "relation/ModifiesPRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/NextRel.h"
#include "relation/NextTRel.h"
#include "relation/ParentRel.h"
#include "relation/ParentTRel.h"
#include "relation/ProcProcRel.h"
#include "relation/ProcVarRel.h"
#include "relation/StmtStmtRel.h"
#include "relation/StmtVarRel.h"
#include "relation/UsesPRel.h"
#include "relation/UsesSRel.h"
#include "with_clause/With.h"

using std::make_shared;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

std::shared_ptr<ResWrapper> DataRetriever::retrieve(StmtVarRel& rel) {
    /*
     * The 9 combinations of LHS and RHS value types are handled:
     * LHS type cannot be wildcard, otherwise semantic error is thrown (covers 3
     * cases); if LHS is concrete ref, RHS is concrete ref OR wildcard, boolean
     * result is expected (covers 2 cases); else if RHS is synonym, then set
     * result is expected (covers 1 case); else if LHS is synonym, then set result
     * is expected (covers 2 case); else the both sides are synonym, table result
     * is expected (covers 1 case).
     */
    auto [lhs_type, rhs_type] = rel.ValTypes();

    std::shared_ptr<ResWrapper> res;
    if (lhs_type == ValType::kLineNum && rhs_type == ValType::kVarName) {
        bool ok = CheckSVRel(rel);
        res = std::make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kLineNum && rhs_type == ValType::kSynonym) {
        shared_ptr<unordered_set<string>> set = GetVarByStmt(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.RhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kVarName) {
        shared_ptr<unordered_set<string>> set = GetStmtByVar(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.LhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kSynonym) {
        shared_ptr<vector<pair<string, string>>> table = GetAllSVRel(rel);
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0},
                                                 {rel.RhsValue(), 1} };
        shared_ptr<TableRes> table_res =
            std::make_shared<TableRes>(syn_to_col, table);

        res = std::make_shared<ResWrapper>(table_res);
    }
    // Wildcard handling cases below
    else if (lhs_type == ValType::kLineNum && rhs_type == ValType::kWildcard) {
        bool ok = CheckSVRelExistenceByStmt(rel);
        res = std::make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kWildcard) {
        shared_ptr<unordered_set<string>> set = GetStmtByWildcard(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.LhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }

    return res;
}

shared_ptr<ResWrapper> DataRetriever::retrieve(ProcVarRel& rel) {
    /*
     * The retrieving logic of ProcVarRel is similar to that of StmtVarRel above.
     */
    auto [lhs_type, rhs_type] = rel.ValTypes();

    std::shared_ptr<ResWrapper> res;
    if (lhs_type == ValType::kProcName && rhs_type == ValType::kVarName) {
        bool ok = CheckPVRel(rel);
        res = std::make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kProcName && rhs_type == ValType::kSynonym) {
        shared_ptr<unordered_set<string>> set = GetVarByProc(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.RhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kVarName) {
        shared_ptr<unordered_set<string>> set = GetProcByVar(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.LhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kSynonym) {
        shared_ptr<vector<pair<string, string>>> table = GetAllPVRel(rel);
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0},
                                                 {rel.RhsValue(), 1} };
        shared_ptr<TableRes> table_res =
            std::make_shared<TableRes>(syn_to_col, table);
        res = std::make_shared<ResWrapper>(table_res);
    }
    // Wildcard handling cases below
    else if (lhs_type == ValType::kProcName && rhs_type == ValType::kWildcard) {
        bool ok = CheckPVRelExistenceByProc(rel);
        res = std::make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kWildcard) {
        shared_ptr<unordered_set<string>> set = GetProcByWildcard(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.LhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }

    return res;
}

std::shared_ptr<ResWrapper> DataRetriever::retrieve(Pattern& pat) {
    /*
     * For a pattern, it has a stmt_synonym_ref and var_ref associated to it;
     * If the var_ref is a variable name, we retrieve all stmt associated with it;
     * If the var_ref is a synonym, we retrieve the table of the stmt synonym and
     * the variable synonym; If the var_ref is a wildcard, we retrieve all
     * available stmt.
     */
    ValType lhs_type = pat.VarValType();

    shared_ptr<unordered_set<string>> set{ nullptr };
    shared_ptr<vector<pair<string, string>>> table{ nullptr };
    if (lhs_type == ValType::kVarName) {
        set = GetPatternStmtByVar(pat);
    }
    else if (lhs_type == ValType::kSynonym) {
        table = GetAllPattern(pat);
    }
    else if (lhs_type == ValType::kWildcard) {
        set = GetPatternStmtByWildcard(pat);
    }

    shared_ptr<ResWrapper> res;
    if (set != nullptr) {
        shared_ptr<SetRes> set_res = make_shared<SetRes>(pat.StmtSyn(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else {
        unordered_map<string, int> syn_to_col = { {pat.StmtSyn(), 0},
                                                 {pat.VarName(), 1} };
        shared_ptr<TableRes> table_res = make_shared<TableRes>(syn_to_col, table);
        res = make_shared<ResWrapper>(table_res);
    }

    return res;
}

std::shared_ptr<ResWrapper> DataRetriever::retrieve(StmtStmtRel& rel) {
    /*
     * Classify LHS x RHS value type combinations by return result type
     * table result:
     *     stmt_syn, stmt_syn -> get table of all pairs.
     *
     * set result:
     *     stmt_syn, wildcard -> get all lhs stmt.
     *     stmt_syn, stmt_num -> get all lhs stmt by rhs stmt_num.
     *     wildcard, stmt_syn -> get all rhs stmt.
     *     stmt_num, stmt_syn -> get all rhs stmt by lhs stmt_num.
     *
     * bool result:
     *     wildcard, wildcard -> check if any relation exists.
     *     wildcard, stmt_num -> get all lhs stmt by rhs stmt_num, and check set
     * emptiness. stmt_num, wildcard -> get all rhs stmt by lhs stmt_num, and
     * check set emptiness. stmt_num, stmt_num -> check relation existence.
     */
    auto [lhs_type, rhs_type] = rel.ValTypes();

    shared_ptr<ResWrapper> res;

    if (lhs_type == ValType::kLineNum && rhs_type == ValType::kLineNum) {
        bool ok = CheckSSRel(rel);
        res = make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kLineNum) {
        shared_ptr<unordered_set<string>> set = GetLhsStmtByRhsStmt(rel);
        shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.LhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kLineNum && rhs_type == ValType::kSynonym) {
        shared_ptr<unordered_set<string>> set = GetRhsStmtByLhsStmt(rel);
        shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.RhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kSynonym) {
        bool are_same_synonyms = rel.LhsValue() == rel.RhsValue();
        if (are_same_synonyms && IsSameSynonymsInvalid(rel)) {
            res = make_shared<ResWrapper>(false);
        }
        else if (are_same_synonyms) {
            shared_ptr<vector<pair<string, string>>> table = GetAllSSRel(rel);
            shared_ptr<unordered_set<string>> set = GetAllEqualRowValues(table);
            shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.LhsValue(), set);
            res = make_shared<ResWrapper>(set_res);
        }
        else {
            shared_ptr<vector<pair<string, string>>> table = GetAllSSRel(rel);
            unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0},
                                                     {rel.RhsValue(), 1} };
            shared_ptr<TableRes> table_res = make_shared<TableRes>(syn_to_col, table);
            res = make_shared<ResWrapper>(table_res);
        }
    }
    // Wildcard handling cases below
    else if (lhs_type == ValType::kWildcard && rhs_type == ValType::kLineNum) {
        bool ok = CheckSSRelExistenceByRhsStmt(rel);
        res = make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kWildcard && rhs_type == ValType::kSynonym) {
        shared_ptr<unordered_set<string>> set = GetRhsStmtByWildcard(rel);
        shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.RhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kLineNum && rhs_type == ValType::kWildcard) {
        bool ok = CheckSSRelExistenceByLhsStmt(rel);
        res = make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kWildcard) {
        shared_ptr<unordered_set<string>> set = GetLhsStmtByWildcard(rel);
        shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.LhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kWildcard && rhs_type == ValType::kWildcard) {
        bool ok = CheckSSRelExistence(rel);
        res = make_shared<ResWrapper>(ok);
    }

    return res;
}

shared_ptr<ResWrapper> DataRetriever::retrieve(ProcProcRel& rel) {
    /*
     * The retreiving logic of ProcProcRel is similar to that of StmtStmtRel
     * above.
     */

    auto [lhs_type, rhs_type] = rel.ValTypes();

    shared_ptr<ResWrapper> res;

    if (lhs_type == ValType::kProcName && rhs_type == ValType::kProcName) {
        bool ok = CheckPPRel(rel);
        res = make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kProcName) {
        auto set = GetLhsProcByRhsProc(rel);
        shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.LhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kProcName && rhs_type == ValType::kSynonym) {
        auto set = GetRhsProcByLhsProc(rel);
        shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.RhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kSynonym) {
        bool are_same_synonyms = rel.LhsValue() == rel.RhsValue();
        if (are_same_synonyms && IsSameSynonymsInvalid(rel)) {
            res = make_shared<ResWrapper>(false);
        }
        else {
            auto table = GetAllPPRel(rel);
            unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0},
                                                     {rel.RhsValue(), 1} };
            shared_ptr<TableRes> table_res = make_shared<TableRes>(syn_to_col, table);
            res = make_shared<ResWrapper>(table_res);
        }
    }
    // Wildcard hanlding cases below
    else if (lhs_type == ValType::kWildcard && rhs_type == ValType::kProcName) {
        auto ok = CheckPPRelExistenceByRhsProc(rel);
        res = make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kWildcard && rhs_type == ValType::kSynonym) {
        auto set = GetRhsProcByWildcard(rel);
        shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.RhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kProcName && rhs_type == ValType::kWildcard) {
        auto ok = CheckPPRelExistenceByLhsProc(rel);
        res = make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kWildcard) {
        auto set = GetLhsProcByWildcard(rel);
        auto set_res = make_shared<SetRes>(rel.LhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (lhs_type == ValType::kWildcard && rhs_type == ValType::kWildcard) {
        bool ok = CheckPPRelExistence(rel);
        res = make_shared<ResWrapper>(ok);
    }

    return res;
}

shared_ptr<ResWrapper> DataRetriever::retrieve(shared_ptr<Ref> ref_ptr) {
    shared_ptr<SetRes> res;
    auto ref_type = ref_ptr->GetRefType();

    shared_ptr<unordered_set<StmtNum>> stmt_set{ nullptr };
    shared_ptr<unordered_set<string>> str_set{ nullptr };
    if (ref_type == RefType::kProcRef) {
        str_set = pkb_ptr_->GetAllProcedures();
    }
    else if (ref_type == RefType::kVarRef) {
        str_set = pkb_ptr_->GetAllVariables();
    }
    else if (ref_type == RefType::kConstRef) {
        stmt_set = pkb_ptr_->GetAllConstants();
    }
    else if (ref_type == RefType::kStmtRef) {
        stmt_set = pkb_ptr_->GetAllStatements();
    }
    else if (ref_type == RefType::kAssignRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kAssignRef);
    }
    else if (ref_type == RefType::kCallRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kCallRef);
    }
    else if (ref_type == RefType::kIfRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kIfRef);
    }
    else if (ref_type == RefType::kWhileRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kWhileRef);
    }
    else if (ref_type == RefType::kReadRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kReadRef);
    }
    else if (ref_type == RefType::kPrintRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kPrintRef);
    }

    if (stmt_set != nullptr) {
        str_set = StmtSetToStrSet(stmt_set);
    }

    string syn = ref_ptr->GetName();
    shared_ptr<SetRes> set_res = shared_ptr<SetRes>(new SetRes(syn, str_set));
    return make_shared<ResWrapper>(set_res);
}

std::shared_ptr<ResWrapper> DataRetriever::retrieve(With& with) {
    /*
     * Each LHS and RHS reference in With clause can be one of {kInt, kString,
     * kSynonym} bool result: (int, int) -> test equality. (string, string) ->
     * test equality. (int, string) -> false. (string, int) -> false.
     *
     * set result:
     *     (int, synonym) -> get all possible values of synonym, then filter by
     * LHS value. (string, synonym) -> get all possible values of synonym, then
     * filter by LHS value. (synonym, int) -> get all possible values of synonym,
     * then filter by RHS value. (synonym, string) -> get all possible values of
     * synonym, then filter by RHS value.
     *
     * table result:
     *     (synonym, synonym) -> get possible values of each synonym, then
     * intersect.
     */
    auto [lhs_type, rhs_type] = with.ValTypes();

    shared_ptr<ResWrapper> res;
    if ((lhs_type == ValType::kInt && rhs_type == ValType::kInt) ||
        (lhs_type == ValType::kString && rhs_type == ValType::kString)) {
        bool ok = with.LhsValue() == with.RhsValue();
        res = make_shared<ResWrapper>(ok);
    }
    else if ((lhs_type == ValType::kInt && rhs_type == ValType::kString) ||
        (lhs_type == ValType::kString && rhs_type == ValType::kInt)) {
        res = make_shared<ResWrapper>(false);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kSynonym) {
        auto table = GetAllWithClause(with);
        unordered_map<string, int> syn_to_col = { {with.LhsValue(), 0},
                                                 {with.RhsValue(), 1} };
        auto table_res = make_shared<TableRes>(syn_to_col, table);
        res = make_shared<ResWrapper>(table_res);
    }
    else if (lhs_type == ValType::kSynonym) {
        auto rhs_val = with.RhsValue();
        auto set = GetWithClauseByRefTypeAndFilterVal(with.LhsRefType(),
            with.LhsAttrType(), rhs_val);
        auto syn_name = with.LhsValue();
        auto set_res = make_shared<SetRes>(syn_name, set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (rhs_type == ValType::kSynonym) {
        auto lhs_val = with.LhsValue();
        auto set = GetWithClauseByRefTypeAndFilterVal(with.RhsRefType(),
            with.RhsAttrType(), lhs_val);
        auto syn_name = with.RhsValue();
        auto set_res = make_shared<SetRes>(syn_name, set);
        res = make_shared<ResWrapper>(set_res);
    }

    return res;
}

bool DataRetriever::CheckSVRel(StmtVarRel& rel) {
    ClauseType type = rel.GetRelType();

    bool res;
    StmtNum stmt_num = rel.LhsValueAsInt().value_or(-1);
    Variable var_name = rel.RhsValue();
    if (type == ClauseType::kUsesSRel) {
        res = pkb_ptr_->CheckUses(stmt_num, var_name);
    }
    else if (type == ClauseType::kModifiesSRel) {
        res = pkb_ptr_->CheckModifies(stmt_num, var_name);
    }

    return res;
}

bool DataRetriever::CheckSVRelExistenceByStmt(StmtVarRel& rel) {
    ClauseType type = rel.GetRelType();

    shared_ptr<unordered_set<string>> set = GetVarByStmt(rel);

    return !(set->empty());
}

shared_ptr<unordered_set<string>> DataRetriever::GetVarByStmt(StmtVarRel& rel) {
    ClauseType type = rel.GetRelType();

    StmtNum stmt_num = rel.LhsValueAsInt().value_or(-1);
    shared_ptr<unordered_set<string>> res;
    if (type == ClauseType::kUsesSRel) {
        res = pkb_ptr_->GetUsesVarByStmtNum(stmt_num);
    }
    else if (type == ClauseType::kModifiesSRel) {
        res = pkb_ptr_->GetModifiesVarByStmtNum(stmt_num);
    }
    return res;
}

shared_ptr<unordered_set<string>> DataRetriever::GetStmtByVar(StmtVarRel& rel) {
    ClauseType type = rel.GetRelType();

    Variable var_name = rel.RhsValue();
    RefType stmt_type = rel.LhsRefType();
    shared_ptr<unordered_set<StmtNum>> set;
    if (type == ClauseType::kUsesSRel) {
        set = pkb_ptr_->GetUsesStmtNumByVar(var_name, stmt_type);
    }
    else if (type == ClauseType::kModifiesSRel) {
        set = pkb_ptr_->GetModifiesStmtNumByVar(var_name, stmt_type);
    }

    return StmtSetToStrSet(set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetStmtByWildcard(
    StmtVarRel& rel) {
    ClauseType type = rel.GetRelType();

    shared_ptr<unordered_set<StmtNum>> stmt_set;
    RefType stmt_type = rel.LhsRefType();
    if (type == ClauseType::kUsesSRel) {
        stmt_set = pkb_ptr_->GetAllUsesStatements(stmt_type);
    }
    else if (type == ClauseType::kModifiesSRel) {
        stmt_set = pkb_ptr_->GetAllModifiesStatements(stmt_type);
    }

    return StmtSetToStrSet(stmt_set);
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllSVRel(
    StmtVarRel& rel) {
    ClauseType type = rel.GetRelType();

    RefType lhs_stmt_type = rel.LhsRefType();
    shared_ptr<vector<pair<StmtNum, Variable>>> table;
    if (type == ClauseType::kUsesSRel) {
        table = pkb_ptr_->GetAllSVUses();
        table = FilterStmtTableByLhsType(table, lhs_stmt_type);
    }
    else if (type == ClauseType::kModifiesSRel) {
        table = pkb_ptr_->GetAllSVModifies();
        table = FilterStmtTableByLhsType(table, lhs_stmt_type);
    }

    return StmtNameTableToStrStrTable(table);
}

bool DataRetriever::CheckPVRel(ProcVarRel& rel) {
    ClauseType type = rel.GetRelType();

    bool res;
    if (type == ClauseType::kUsesPRel) {
        res = pkb_ptr_->CheckUses(rel.LhsValue(), rel.RhsValue());
    }
    else if (type == ClauseType::kModifiesPRel) {
        res = pkb_ptr_->CheckModifies(rel.LhsValue(), rel.RhsValue());
    }

    return res;
}

bool DataRetriever::CheckPVRelExistenceByProc(ProcVarRel& rel) {
    ClauseType type = rel.GetRelType();

    shared_ptr<unordered_set<Variable>> set = GetVarByProc(rel);

    return !(set->empty());
}

shared_ptr<unordered_set<string>> DataRetriever::GetVarByProc(ProcVarRel& rel) {
    ClauseType type = rel.GetRelType();

    Procedure proc_name = rel.LhsValue();
    shared_ptr<unordered_set<Variable>> res;
    if (type == ClauseType::kUsesPRel) {
        res = pkb_ptr_->GetUsesVarByProcName(proc_name);
    }
    else if (type == ClauseType::kModifiesPRel) {
        res = pkb_ptr_->GetModifiesVarByProcName(proc_name);
    }

    return res;
}

shared_ptr<unordered_set<string>> DataRetriever::GetProcByVar(ProcVarRel& rel) {
    ClauseType type = rel.GetRelType();

    Variable var_name = rel.RhsValue();
    shared_ptr<unordered_set<Variable>> res;
    if (type == ClauseType::kUsesPRel) {
        res = pkb_ptr_->GetUsesProcNameByVar(var_name);
    }
    else if (type == ClauseType::kModifiesPRel) {
        res = pkb_ptr_->GetModifiesProcNameByVar(var_name);
    }

    return res;
}

shared_ptr<unordered_set<string>> DataRetriever::GetProcByWildcard(
    ProcVarRel& rel) {
    ClauseType type = rel.GetRelType();

    shared_ptr<unordered_set<Procedure>> res;
    if (type == ClauseType::kUsesPRel) {
        res = pkb_ptr_->GetAllUsesProcedures();
    }
    else if (type == ClauseType::kModifiesPRel) {
        res = pkb_ptr_->GetAllModifiesProcedures();
    }

    return res;
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllPVRel(
    ProcVarRel& rel) {
    ClauseType type = rel.GetRelType();

    shared_ptr<vector<pair<Procedure, Variable>>> res;
    if (type == ClauseType::kUsesPRel) {
        res = pkb_ptr_->GetAllPVUses();
    }
    else if (type == ClauseType::kModifiesPRel) {
        res = pkb_ptr_->GetAllPVModifies();
    }

    return res;
}

bool DataRetriever::CheckPPRel(ProcProcRel& rel) {
    ClauseType type = rel.GetRelType();

    Procedure lhs_proc_name = rel.LhsValue();
    Procedure rhs_proc_name = rel.RhsValue();
    bool res = false;
    if (type == ClauseType::kCallsRel) {
        res = pkb_ptr_->CheckCalls(lhs_proc_name, rhs_proc_name);
    }
    else if (type == ClauseType::kCallsTRel) {
        res = pkb_ptr_->CheckCallsT(lhs_proc_name, rhs_proc_name);
    }

    return res;
}

bool DataRetriever::CheckPPRelExistence(ProcProcRel& rel) {
    bool is_empty = pkb_ptr_->IsCallsStoreEmpty();

    return !is_empty;
}

bool DataRetriever::CheckPPRelExistenceByRhsProc(ProcProcRel& rel) {
    auto lhs_proc_set = GetLhsProcByRhsProc(rel);

    return !(lhs_proc_set->empty());
}

bool DataRetriever::CheckPPRelExistenceByLhsProc(ProcProcRel& rel) {
    auto rhs_proc_set = GetRhsProcByLhsProc(rel);

    return !(rhs_proc_set->empty());
}

std::shared_ptr<std::unordered_set<std::string>>
DataRetriever::GetRhsProcByLhsProc(ProcProcRel& rel) {
    ClauseType type = rel.GetRelType();

    Procedure lhs_proc_name = rel.LhsValue();
    shared_ptr<unordered_set<Procedure>> set;
    if (type == ClauseType::kCallsRel) {
        set = pkb_ptr_->GetCalleeFromCaller(lhs_proc_name);
    }
    else if (type == ClauseType::kCallsTRel) {
        set = pkb_ptr_->GetAllCalleeFromCaller(lhs_proc_name);
    }

    return set;
}

std::shared_ptr<std::unordered_set<std::string>>
DataRetriever::GetRhsProcByWildcard(ProcProcRel& rel) {
    shared_ptr<unordered_set<Procedure>> set;
    set = pkb_ptr_->GetAllCallees();

    return set;
}

std::shared_ptr<std::unordered_set<std::string>>
DataRetriever::GetLhsProcByRhsProc(ProcProcRel& rel) {
    ClauseType type = rel.GetRelType();

    Procedure rhs_proc_name = rel.RhsValue();
    shared_ptr<unordered_set<Procedure>> set;
    if (type == ClauseType::kCallsRel) {
        set = pkb_ptr_->GetCallerFromCallee(rhs_proc_name);
    }
    else if (type == ClauseType::kCallsTRel) {
        set = pkb_ptr_->GetAllCallerFromCallee(rhs_proc_name);
    }

    return set;
}

std::shared_ptr<std::unordered_set<std::string>>
DataRetriever::GetLhsProcByWildcard(ProcProcRel& rel) {
    Procedure rhs_proc_name = rel.RhsValue();
    shared_ptr<unordered_set<Procedure>> set;
    set = pkb_ptr_->GetAllCallers();

    return set;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
DataRetriever::GetAllPPRel(ProcProcRel& rel) {
    ClauseType type = rel.GetRelType();

    shared_ptr<vector<StrPair>> table{ nullptr };
    if (type == ClauseType::kCallsRel) {
        table = pkb_ptr_->GetAllCallsRelations();
    }
    else if (type == ClauseType::kCallsTRel) {
        table = pkb_ptr_->GetAllCallsTRelations();
    }

    return table;
}

bool DataRetriever::CheckSSRel(StmtStmtRel& rel) {
    ClauseType type = rel.GetRelType();

    StmtNum lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    StmtNum rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    bool res = false;
    if (type == ClauseType::kParentRel) {
        res = pkb_ptr_->CheckParent(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == ClauseType::kParentTRel) {
        res = pkb_ptr_->CheckParentT(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == ClauseType::kFollowsRel) {
        res = pkb_ptr_->CheckFollows(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == ClauseType::kFollowsTRel) {
        res = pkb_ptr_->CheckFollowsT(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == ClauseType::kNextRel) {
        res = pkb_ptr_->CheckNext(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == ClauseType::kNextTRel) {
        res = pkb_ptr_->CheckNextT(lhs_stmt_num, rhs_stmt_num);
    }

    // WIP
    /*
    else if (type == ClauseType::kAffectsRel) {
        res = pkb_ptr_->CheckAffects(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == ClauseType::kAffectsTRel) {
        res = pkb_ptr_->CheckAffectsT(lhs_stmt_num, rhs_stmt_num);
    }*/

    return res;
}

bool DataRetriever::CheckSSRelExistence(StmtStmtRel& rel) {
    ClauseType type = rel.GetRelType();

    bool is_empty{ false };
    if (type == ClauseType::kParentRel || type == ClauseType::kParentTRel) {
        is_empty = pkb_ptr_->IsParentStoreEmpty();
    }
    else if (type == ClauseType::kFollowsRel ||
        type == ClauseType::kFollowsTRel) {
        is_empty = pkb_ptr_->IsFollowsStoreEmpty();
    }

    // WIP
    /*
    else if (type == ClauseType::kNextRel || type == ClauseType::kNextTRel) {
        is_empty = pkb_ptr_->IsNextStoreEmpty();
    }
    else if (type == ClauseType::kAffectsRel || type == ClauseType::kAffectsTRel)
    { is_empty = pkb_ptr_->IsAffectsStoreEmpty();
    }
    */

    return !is_empty;
}

bool DataRetriever::CheckSSRelExistenceByRhsStmt(StmtStmtRel& rel) {
    ClauseType type = rel.GetRelType();

    StmtNum rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    shared_ptr<unordered_set<StmtNum>> stmt_set;
    if (type == ClauseType::kParentRel) {
        stmt_set = pkb_ptr_->GetParentFromStmt(rhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == ClauseType::kParentTRel) {
        stmt_set = pkb_ptr_->GetAllParentsFromStmt(rhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == ClauseType::kFollowsRel) {
        stmt_set =
            pkb_ptr_->GetPredecessorStmtFromStmt(rhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == ClauseType::kFollowsTRel) {
        stmt_set = pkb_ptr_->GetAllPredecessorStmtsFromStmt(rhs_stmt_num,
            RefType::kStmtRef);
    }
    else if (type == ClauseType::kNextRel) {
        stmt_set = pkb_ptr_->GetPrevStmtsFromStmt(rhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == ClauseType::kNextTRel) {
        stmt_set =
            pkb_ptr_->GetAllPrevStmtsFromStmt(rhs_stmt_num, RefType::kStmtRef);
    }

    // WIP
    /*
    else if (type == ClauseType::kAffectsRel) {

    }
    else if (type == ClauseType::kAffectsTRel) {

    }
    */

    return !(stmt_set->empty());
}

bool DataRetriever::CheckSSRelExistenceByLhsStmt(StmtStmtRel& rel) {
    ClauseType type = rel.GetRelType();

    StmtNum lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    shared_ptr<unordered_set<StmtNum>> stmt_set;
    if (type == ClauseType::kParentRel) {
        stmt_set = pkb_ptr_->GetChildrenFromStmt(lhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == ClauseType::kParentTRel) {
        stmt_set =
            pkb_ptr_->GetAllChildrenFromStmt(lhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == ClauseType::kFollowsRel) {
        stmt_set =
            pkb_ptr_->GetSuccessorStmtFromStmt(lhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == ClauseType::kFollowsTRel) {
        stmt_set =
            pkb_ptr_->GetAllSuccessorStmtsFromStmt(lhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == ClauseType::kNextRel) {
        stmt_set = pkb_ptr_->GetNextStmtsFromStmt(lhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == ClauseType::kNextTRel) {
        stmt_set =
            pkb_ptr_->GetAllNextStmtsFromStmt(lhs_stmt_num, RefType::kStmtRef);
    }

    // WIP
    /*
    else if (type == ClauseType::kAffectsRel) {

    }
    else if (type == ClauseType::kAffectsTRel) {

    }
    */

    return !(stmt_set->empty());
}

std::shared_ptr<unordered_set<string>> DataRetriever::GetRhsStmtByLhsStmt(
    StmtStmtRel& rel) {
    ClauseType type = rel.GetRelType();

    StmtNum lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    RefType rhs_stmt_type = rel.RhsRefType();
    shared_ptr<unordered_set<StmtNum>> stmt_set;
    if (type == ClauseType::kParentRel) {
        stmt_set = pkb_ptr_->GetChildrenFromStmt(lhs_stmt_num, rhs_stmt_type);
    }
    else if (type == ClauseType::kParentTRel) {
        stmt_set = pkb_ptr_->GetAllChildrenFromStmt(lhs_stmt_num, rhs_stmt_type);
    }
    else if (type == ClauseType::kFollowsRel) {
        stmt_set = pkb_ptr_->GetSuccessorStmtFromStmt(lhs_stmt_num, rhs_stmt_type);
    }
    else if (type == ClauseType::kFollowsTRel) {
        stmt_set =
            pkb_ptr_->GetAllSuccessorStmtsFromStmt(lhs_stmt_num, rhs_stmt_type);
    }
    else if (type == ClauseType::kNextRel) {
        stmt_set = pkb_ptr_->GetNextStmtsFromStmt(lhs_stmt_num, rhs_stmt_type);
    }
    else if (type == ClauseType::kNextTRel) {
        stmt_set = pkb_ptr_->GetAllNextStmtsFromStmt(lhs_stmt_num, rhs_stmt_type);
    }

    // WIP
    /*
    else if (type == ClauseType::kAffectsRel) {

    }
    else if (type == ClauseType::kAffectsTRel) {

    }
    */

    return StmtSetToStrSet(stmt_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetRhsStmtByWildcard(
    StmtStmtRel& rel) {
    ClauseType type = rel.GetRelType();

    shared_ptr<unordered_set<StmtNum>> stmt_set;
    RefType rhs_stmt_type = rel.RhsRefType();
    if (type == ClauseType::kParentRel || type == ClauseType::kParentTRel) {
        stmt_set = pkb_ptr_->GetAllChildren(rhs_stmt_type);
    }
    else if (type == ClauseType::kFollowsRel ||
        type == ClauseType::kFollowsTRel) {
        stmt_set = pkb_ptr_->GetAllSuccessorStmts(rhs_stmt_type);
    }
    else if (type == ClauseType::kNextRel || type == ClauseType::kNextTRel) {
        stmt_set = pkb_ptr_->GetAllNextStmts(rhs_stmt_type);
    }

    // WIP
    /*
    else if (type == ClauseType::kAffectsRel || type == ClauseType::kAffectsTRel)
    {

    }
    */

    return StmtSetToStrSet(stmt_set);
}

std::shared_ptr<unordered_set<string>> DataRetriever::GetLhsStmtByRhsStmt(
    StmtStmtRel& rel) {
    ClauseType type = rel.GetRelType();

    StmtNum rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    RefType lhs_stmt_type = rel.LhsRefType();
    shared_ptr<unordered_set<StmtNum>> stmt_set;
    if (type == ClauseType::kParentRel) {
        stmt_set = pkb_ptr_->GetParentFromStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == ClauseType::kParentTRel) {
        stmt_set = pkb_ptr_->GetAllParentsFromStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == ClauseType::kFollowsRel) {
        stmt_set =
            pkb_ptr_->GetPredecessorStmtFromStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == ClauseType::kFollowsTRel) {
        stmt_set =
            pkb_ptr_->GetAllPredecessorStmtsFromStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == ClauseType::kNextRel) {
        stmt_set = pkb_ptr_->GetPrevStmtsFromStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == ClauseType::kNextTRel) {
        stmt_set = pkb_ptr_->GetAllPrevStmtsFromStmt(rhs_stmt_num, lhs_stmt_type);
    }

    // WIP
    /*
    else if (type == ClauseType::kAffectsRel) {

    }
    else if (type == ClauseType::kAffectsTRel) {

    }
    */

    return StmtSetToStrSet(stmt_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetLhsStmtByWildcard(
    StmtStmtRel& rel) {
    ClauseType type = rel.GetRelType();

    shared_ptr<unordered_set<StmtNum>> stmt_set;
    RefType lhs_stmt_type = rel.LhsRefType();
    if (type == ClauseType::kParentRel || type == ClauseType::kParentTRel) {
        stmt_set = pkb_ptr_->GetAllParents(lhs_stmt_type);
    }
    else if (type == ClauseType::kFollowsRel ||
        type == ClauseType::kFollowsTRel) {
        stmt_set = pkb_ptr_->GetAllPredecessorStmts(lhs_stmt_type);
    }
    else if (type == ClauseType::kNextRel || type == ClauseType::kNextTRel) {
        stmt_set = pkb_ptr_->GetAllPrevStmts(lhs_stmt_type);
    }

    // WIP
    /*
    else if (type == ClauseType::kAffectsRel || type == ClauseType::kAffectsTRel)
    {

    }
    */

    return StmtSetToStrSet(stmt_set);
}

std::shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllSSRel(
    StmtStmtRel& rel) {
    ClauseType type = rel.GetRelType();

    RefType lhs_stmt_type = rel.LhsRefType();
    RefType rhs_stmt_type = rel.RhsRefType();
    shared_ptr<vector<pair<StmtNum, StmtNum>>> table;
    if (type == ClauseType::kParentRel) {
        table = pkb_ptr_->GetAllParentRelations();
    }
    else if (type == ClauseType::kParentTRel) {
        table = pkb_ptr_->GetAllParentTRelations();
    }
    else if (type == ClauseType::kFollowsRel) {
        table = pkb_ptr_->GetAllFollowsRelations();
    }
    else if (type == ClauseType::kFollowsTRel) {
        table = pkb_ptr_->GetAllFollowsTRelations();
    }
    else if (type == ClauseType::kNextRel) {
        table = pkb_ptr_->GetAllNextRelations();
    }
    else if (type == ClauseType::kNextTRel) {
        table = pkb_ptr_->GetAllNextTRelations();
    }

    // WIP
    /*
    else if (type == ClauseType::kAffectsRel) {

    }
    else if (type == ClauseType::kAffectsTRel) {

    }
    */
    table = FilterStmtTableByTypes(table, lhs_stmt_type, rhs_stmt_type);

    return StmtStmtTableToStrStrTable(table);
}

std::shared_ptr<std::unordered_set<std::string>>
DataRetriever::GetPatternStmtByVar(Pattern& pat) {
    auto type = pat.GetPatternType();

    shared_ptr<unordered_set<string>> set;
    if (type == ClauseType::kAssignPattern) {
        set = GetAssignPatternStmtByVar(static_cast<AssignPattern&>(pat));
    }
    else if (type == ClauseType::kIfPattern) {
        set = GetIfPatternStmtByVar(static_cast<IfPattern&>(pat));
    }
    else if (type == ClauseType::kWhilePattern) {
        set = GetWhilePatternStmtByVar(static_cast<WhilePattern&>(pat));
    }

    return set;
}

std::shared_ptr<std::unordered_set<std::string>>
DataRetriever::GetPatternStmtByWildcard(Pattern& pat) {
    auto type = pat.GetPatternType();

    shared_ptr<unordered_set<string>> set;
    if (type == ClauseType::kAssignPattern) {
        set = GetAssignPatternStmtByWildcard(static_cast<AssignPattern&>(pat));
    }
    else if (type == ClauseType::kIfPattern) {
        set = GetIfPatternStmtByWildcard(static_cast<IfPattern&>(pat));
    }
    else if (type == ClauseType::kWhilePattern) {
        set = GetWhilePatternStmtByWildcard(static_cast<WhilePattern&>(pat));
    }

    return set;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
DataRetriever::GetAllPattern(Pattern& pat) {
    auto type = pat.GetPatternType();

    shared_ptr<vector<StrPair>> table;
    if (type == ClauseType::kAssignPattern) {
        table = GetAllAssignPattern(static_cast<AssignPattern&>(pat));
    }
    else if (type == ClauseType::kIfPattern) {
        table = GetAllIfPattern(static_cast<IfPattern&>(pat));
    }
    else if (type == ClauseType::kWhilePattern) {
        table = GetAllWhilePattern(static_cast<WhilePattern&>(pat));
    }

    return table;
}

shared_ptr<unordered_set<string>> DataRetriever::GetAssignPatternStmtByVar(
    AssignPattern& pat) {
    auto var_name = pat.VarName();
    shared_ptr<ExprSpec> expr_spec_ptr = pat.GetExprSpec();

    shared_ptr<unordered_set<StmtNum>> stmt_set =
        make_shared<unordered_set<StmtNum>>();
    if (expr_spec_ptr->IsWildcard()) {
        stmt_set = pkb_ptr_->GetModifiesStmtNumByVar(var_name, RefType::kAssignRef);
    }
    else {
        stmt_set = pkb_ptr_->FilterByAssignPatternMatch(var_name, expr_spec_ptr);
    }

    return StmtSetToStrSet(stmt_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetAssignPatternStmtByWildcard(
    AssignPattern& pat) {
    shared_ptr<ExprSpec> expr_spec_ptr = pat.GetExprSpec();
    shared_ptr<unordered_set<StmtNum>> stmt_set =
        std::make_shared<unordered_set<StmtNum>>();
    if (expr_spec_ptr->IsWildcard()) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kAssignRef);
    }
    else {
        stmt_set = pkb_ptr_->FilterByAssignPatternMatch(expr_spec_ptr);
    }

    return StmtSetToStrSet(stmt_set);
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllAssignPattern(
    AssignPattern& pat) {
    shared_ptr<ExprSpec> expr_spec_ptr = pat.GetExprSpec();
    shared_ptr<vector<pair<StmtNum, Variable>>> stmt_var_table =
        pkb_ptr_->GetAssignPatternMatch(expr_spec_ptr);

    return StmtNameTableToStrStrTable(stmt_var_table);
}

shared_ptr<unordered_set<string>> DataRetriever::GetIfPatternStmtByVar(
    IfPattern& pat) {
    Variable var_name = pat.VarName();
    shared_ptr<unordered_set<StmtNum>> stmt_set =
        pkb_ptr_->GetAllIfPatternStatmentsFromVar(var_name);

    return StmtSetToStrSet(stmt_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetIfPatternStmtByWildcard(
    IfPattern& pat) {
    shared_ptr<unordered_set<StmtNum>> stmt_set =
        pkb_ptr_->GetAllIfPatternStatements();

    return StmtSetToStrSet(stmt_set);
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllIfPattern(
    IfPattern& pat) {
    shared_ptr<vector<pair<StmtNum, Variable>>> table =
        pkb_ptr_->GetAllIfPatterns();

    return StmtNameTableToStrStrTable(table);
}

shared_ptr<unordered_set<string>> DataRetriever::GetWhilePatternStmtByVar(
    WhilePattern& pat) {
    Variable var_name = pat.VarName();
    shared_ptr<unordered_set<StmtNum>> stmt_set =
        pkb_ptr_->GetAllWhilePatternStatmentsFromVar(var_name);

    return StmtSetToStrSet(stmt_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetWhilePatternStmtByWildcard(
    WhilePattern& pat) {
    shared_ptr<unordered_set<StmtNum>> stmt_set =
        pkb_ptr_->GetAllWhilePatternStatements();

    return StmtSetToStrSet(stmt_set);
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllWhilePattern(
    WhilePattern& pat) {
    shared_ptr<vector<pair<StmtNum, Variable>>> table =
        pkb_ptr_->GetAllWhilePatterns();

    return StmtNameTableToStrStrTable(table);
}

std::shared_ptr<std::unordered_set<std::string>>
DataRetriever::GetWithClauseBySingleAttrTypeRefType(RefType syn_ref_type) {
    shared_ptr<unordered_set<string>> str_set{ nullptr };
    shared_ptr<unordered_set<StmtNum>> stmt_set{ nullptr };

    if (syn_ref_type == RefType::kProcRef) {
        str_set = pkb_ptr_->GetAllProcedures();
    }
    else if (syn_ref_type == RefType::kVarRef) {
        str_set = pkb_ptr_->GetAllVariables();
    }
    else if (syn_ref_type == RefType::kConstRef) {
        stmt_set = pkb_ptr_->GetAllConstants();
    }
    else if (syn_ref_type == RefType::kStmtRef) {
        stmt_set = pkb_ptr_->GetAllStatements();
    }
    else if (syn_ref_type == RefType::kIfRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kIfRef);
    }
    else if (syn_ref_type == RefType::kWhileRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kWhileRef);
    }
    else if (syn_ref_type == RefType::kAssignRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kAssignRef);
    }
    else if (syn_ref_type == RefType::kReadRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kReadRef);
    }
    else if (syn_ref_type == RefType::kPrintRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kPrintRef);
    }
    else if (syn_ref_type == RefType::kCallRef) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kCallRef);
    }

    if (stmt_set != nullptr) {
        str_set = StmtSetToStrSet(stmt_set);
    }
    return str_set;
}

std::shared_ptr<std::unordered_set<std::string>>
DataRetriever::GetWithClauseByMultipleAttrTypeRefType(RefType syn_ref_type,
    AttrType attr_type,
    string& pivot_val) {
    shared_ptr<unordered_set<string>> str_set{ nullptr };
    shared_ptr<unordered_set<StmtNum>> stmt_set{ nullptr };
    bool need_filter{ false };
    if (syn_ref_type == RefType::kReadRef) {
        if (attr_type == AttrType::kVarName) {
            stmt_set = pkb_ptr_->GetReadStatementFromVariable(pivot_val);
        }
        else if (attr_type == AttrType::kStmtNum) {
            stmt_set = pkb_ptr_->GetStatementsByType(RefType::kReadRef);
            need_filter = true;
        }
    }
    else if (syn_ref_type == RefType::kPrintRef) {
        if (attr_type == AttrType::kVarName) {
            stmt_set = pkb_ptr_->GetPrintStatementFromVariable(pivot_val);
        }
        else if (attr_type == AttrType::kStmtNum) {
            stmt_set = pkb_ptr_->GetStatementsByType(RefType::kPrintRef);
            need_filter = true;
        }
    }
    else if (syn_ref_type == RefType::kCallRef) {
        if (attr_type == AttrType::kProcName) {
            stmt_set = pkb_ptr_->GetCallsStatementFromProcedure(pivot_val);
        }
        else if (attr_type == AttrType::kStmtNum) {
            stmt_set = pkb_ptr_->GetStatementsByType(RefType::kCallRef);
            need_filter = true;
        }
    }

    if (stmt_set != nullptr) {
        str_set = StmtSetToStrSet(stmt_set);
    }
    if (need_filter) {
        str_set = FilterSetByValue(str_set, pivot_val);
    }
    return str_set;
}

std::shared_ptr<std::unordered_set<string>>
DataRetriever::GetWithClauseByRefTypeAndFilterVal(RefType syn_ref_type,
    AttrType attr_type,
    string& filter_val) {
    shared_ptr<unordered_set<string>> str_set{ nullptr };

    unordered_set<RefType>single_attr_type_ref_types{
        RefType::kProcRef,  RefType::kVarRef, RefType::kConstRef,
        RefType::kStmtRef,  RefType::kIfRef,  RefType::kWhileRef,
        RefType::kAssignRef };
    if (single_attr_type_ref_types.count(syn_ref_type) > 0) {
        str_set = GetWithClauseBySingleAttrTypeRefType(syn_ref_type);
        str_set = FilterSetByValue(str_set, filter_val);
    }
    else {
        str_set = GetWithClauseByMultipleAttrTypeRefType(syn_ref_type, attr_type,
            filter_val);
    }

    return str_set;
}

std::shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllWithClause(
    With& with) {

    auto lhs_ref_type = with.LhsRefType();
    auto rhs_ref_type = with.RhsRefType();
    shared_ptr<unordered_set<string>> set1{ nullptr };
    shared_ptr<vector<pair<string, string>>> table1{ nullptr };
    if (with.IsLhsAttrTypeDefault()) {
        set1 = GetWithClauseBySingleAttrTypeRefType(lhs_ref_type);
    }
    else {
        table1 = GetWithClauseAttrPairs(lhs_ref_type);
    }

    shared_ptr<unordered_set<string>> set2{ nullptr };
    shared_ptr<vector<pair<string, string>>> table2{ nullptr };
    if (with.IsRhsAttrTypeDefault()) {
        set2 = GetWithClauseBySingleAttrTypeRefType(rhs_ref_type);
    }
    else {
        table2 = GetWithClauseAttrPairs(rhs_ref_type);
    }

    auto joined_table = make_shared<vector<pair<string, string>>>();
    if (set1 != nullptr && set2 != nullptr) {
        joined_table = JoinWithClauseSets(set1, set2);
    }
    else if (set1 != nullptr && table2 != nullptr) {
        joined_table = JoinWithClauseSetAndTable(set1, table2);
    }
    else if (table1 != nullptr && set1 != nullptr) {
        joined_table = JoinWithClauseSetAndTable(table1, set2);
    }
    else if (table1 != nullptr && table2 != nullptr) {
        joined_table = JoinWithClauseTables(table1, table2);
    }

    return joined_table;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>> DataRetriever::GetWithClauseAttrPairs(RefType syn_ref_type) {

    shared_ptr<vector<pair<shared_ptr<StmtNum>, shared_ptr<Procedure>>>> stmt_proc_table{ nullptr };
    shared_ptr<vector<pair<shared_ptr<StmtNum>, shared_ptr<Variable>>>> stmt_var_table{ nullptr };
    if (syn_ref_type == RefType::kCallRef) {
        stmt_proc_table = pkb_ptr_->GetAllCallsStatementProcedurePairs();
    }
    else if (syn_ref_type == RefType::kReadRef) {
        stmt_var_table = pkb_ptr_->GetAllReadStatementVariablePairs();
    }
    else if (syn_ref_type == RefType::kPrintRef) {
        stmt_var_table = pkb_ptr_->GetAllPrintStatementVariablePairs();
    }

    auto res_table = make_shared<vector<pair<string, string>>>();
    if (stmt_proc_table != nullptr) {
        res_table = StmtptrNameptrTableToStrStrTable(stmt_proc_table);
    }
    else {
        res_table = StmtptrNameptrTableToStrStrTable(stmt_var_table);
    }

    return res_table;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>> DataRetriever::JoinWithClauseSets(std::shared_ptr<std::unordered_set<std::string>> set1, std::shared_ptr<std::unordered_set<std::string>> set2) {
    if (set1->size() > set2->size()) {
        auto temp_ptr = set1;
        set1 = set2;
        set2 = temp_ptr;
    }

    auto table = make_shared<vector<pair<string, string>>>();
    for (auto& value : *set1) {
        if (set2->find(value) != set2->end()) {
            table->push_back(make_pair(value, value));
        }
    }

    return table;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>> DataRetriever::JoinWithClauseSetAndTable(std::shared_ptr<std::unordered_set<std::string>> set1, std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table2) {
    auto joined_table = make_shared<vector<pair<string, string>>>();
    for (auto& [default_value, join_value] : *table2) {
        if (set1->find(join_value) != set1->end()) {
            joined_table->push_back(make_pair(join_value, default_value));
        }
    }

    return joined_table;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>> DataRetriever::JoinWithClauseSetAndTable(std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table1, std::shared_ptr<std::unordered_set<std::string>> set2) {
    auto joined_table = make_shared<vector<pair<string, string>>>();
    for (auto& [default_value, join_value] : *table1) {
        if (set2->find(join_value) != set2->end()) {
            joined_table->push_back(make_pair(default_value, join_value));
        }
    }

    return joined_table;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>> DataRetriever::JoinWithClauseTables(std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table1, std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table2) {
    unordered_set<string> key_set;
    for (auto& [val, key] : *table1) {
        key_set.insert(key);
    }

    auto joined_table = make_shared<vector<pair<string, string>>>();
    for (auto& [default_value, key_value] : *table2) {
        if (key_set.find(key_value) != key_set.end()) {
            joined_table->push_back(make_pair(default_value, default_value));
        }
    }

    return joined_table;
}

std::shared_ptr<Procedure> DataRetriever::MapCallsStmtNumToProcName(std::string& stmt_num_str) {
    return pkb_ptr_->GetCallsProcedureFromStatement(std::stoi(stmt_num_str));
}

std::shared_ptr<Variable> DataRetriever::MapReadStmtNumToVarName(std::string& stmt_num_str) {
    return pkb_ptr_->GetReadVariableFromStatement(std::stoi(stmt_num_str));
}

std::shared_ptr<Variable> DataRetriever::MapPrintStmtNumToVarName(std::string& stmt_num_str) {
    return pkb_ptr_->GetPrintVariableFromStatement(std::stoi(stmt_num_str));
}

shared_ptr<unordered_set<string>> DataRetriever::StmtSetToStrSet(
    shared_ptr<unordered_set<int>> set) {
    auto res = make_shared<unordered_set<string>>();
    for (auto iter = set->begin(); iter != set->end(); ++iter) {
        res->insert(std::to_string(*iter));
    }

    return res;
}

std::shared_ptr<vector<pair<string, string>>>
DataRetriever::StmtNameTableToStrStrTable(
    std::shared_ptr<vector<pair<int, string>>> table) {
    auto res = make_shared<vector<pair<string, string>>>();
    for (auto iter = table->begin(); iter != table->end(); ++iter) {
        auto& [k1, k2] = *iter;
        res->push_back(std::make_pair(std::to_string(k1), k2));
    }

    return res;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>> 
DataRetriever::StmtptrNameptrTableToStrStrTable(
    std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<std::string>>>> table) {

    auto res = make_shared<vector<pair<string, string>>>();
    for (auto iter = table->begin(); iter != table->end(); ++iter) {
        auto& [k1, k2] = *iter;
        res->push_back(std::make_pair(std::to_string(*k1), *k2));
    }

    return res;
}

std::shared_ptr<vector<pair<string, string>>>
DataRetriever::StmtStmtTableToStrStrTable(
    std::shared_ptr<vector<pair<int, int>>> table) {
    auto res = make_shared<vector<pair<string, string>>>();
    for (auto iter = table->begin(); iter != table->end(); ++iter) {
        auto& [k1, k2] = *iter;
        res->push_back(std::make_pair(std::to_string(k1), std::to_string(k2)));
    }

    return res;
}

bool DataRetriever::IsSameSynonymsInvalid(StmtStmtRel & rel) {
    auto rel_type = rel.GetRelType();
    if (rel_type == ClauseType::kNextTRel ||
        rel_type == ClauseType::kAffectsRel ||
        rel_type == ClauseType::kAffectsTRel) {
        // Relations that can have same synonyms on both sides.
        return false;
    }

    return true;
}

bool DataRetriever::IsSameSynonymsInvalid(ProcProcRel & rel) {
    // So far all Proc-Proc relation cannot have same synonyms on both sides.
    return true;
}

shared_ptr<vector<pair<StmtNum, StmtNum>>>
DataRetriever::FilterStmtTableByTypes(
    shared_ptr<vector<pair<StmtNum, StmtNum>>> table, RefType lhs_stmt_type,
    RefType rhs_stmt_type) {
    if (lhs_stmt_type == RefType::kStmtRef &&
        rhs_stmt_type == RefType::kStmtRef) {
        return table;
    }

    shared_ptr<vector<pair<StmtNum, StmtNum>>> res;
    if (lhs_stmt_type != RefType::kStmtRef &&
        rhs_stmt_type != RefType::kStmtRef) {
        res = FilterStmtTableByBothTypes(table, lhs_stmt_type, rhs_stmt_type);
    }
    else if (lhs_stmt_type != RefType::kStmtRef) {
        res = FilterStmtTableByLhsType(table, lhs_stmt_type);
    }
    else if (rhs_stmt_type != RefType::kStmtRef) {
        res = FilterStmtTableByRhsType(table, rhs_stmt_type);
    }

    return res;
}

shared_ptr<vector<pair<StmtNum, StmtNum>>>
DataRetriever::FilterStmtTableByBothTypes(
    shared_ptr<vector<pair<StmtNum, StmtNum>>> table, RefType lhs_stmt_type,
    RefType rhs_stmt_type) {
    auto lhs_type_predicate = [this, lhs_stmt_type](StmtNum stmt) -> bool {
        return *(this->pkb_ptr_->GetStatementType(stmt)) == lhs_stmt_type;
    };
    auto rhs_type_predicate = [this, rhs_stmt_type](StmtNum stmt) -> bool {
        return *(this->pkb_ptr_->GetStatementType(stmt)) == rhs_stmt_type;
    };

    auto res = make_shared<vector<pair<StmtNum, StmtNum>>>();
    for (auto iter = table->begin(); iter != table->end(); ++iter) {
        if (lhs_type_predicate(iter->first) && rhs_type_predicate(iter->second)) {
            res->push_back(*iter);
        }
    }

    return res;
}
