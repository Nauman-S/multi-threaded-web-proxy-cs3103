#include "DataRetriever.h"

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cassert>

#include "pattern/Pattern.h"
#include "pattern/AssignPattern.h"
#include "pattern/IfPattern.h"
#include "pattern/WhilePattern.h"
#include "pattern/PatternType.h"
#include "relation/StmtVarRel.h"
#include "relation/ProcVarRel.h"
#include "relation/ProcProcRel.h"
#include "relation/StmtStmtRel.h"
#include "relation/UsesSRel.h"
#include "relation/UsesPRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/ModifiesPRel.h"
#include "relation/FollowsRel.h"
#include "relation/FollowsTRel.h"
#include "relation/ParentRel.h"
#include "relation/ParentTRel.h"
#include "relation/CallsRel.h"
#include "relation/CallsTRel.h"
#include "relation/NextRel.h"
#include "relation/NextTRel.h"
#include "relation/AffectsRel.h"
#include "relation/AffectsTRel.h"
#include "relation/RelType.h"
#include "reference/ValType.h"
#include "with_clause/With.h"
#include "../PKB/ReadPKBManager.h"
#include "../PKB/manager/UsesManager.h"
#include "../Utils/type/TypeDef.h"

using std::string;
using std::unordered_set;
using std::unordered_map;
using std::vector;
using std::pair;
using std::shared_ptr;
using std::make_shared;


std::shared_ptr<ResWrapper> DataRetriever::retrieve(StmtVarRel& rel)
{
    /*
        There are in total 9 combinations of LHS and RHS value types.
        LHS type cannot be wildcard, otherwise semantic error is thrown (covers 3 cases);
        if LHS is concrete ref, RHS is concrete ref OR wildcard, boolean result is expected (covers 2 cases);
        else if RHS is synonym, then set result is expected (covers 1 case);
        else if LHS is synonym, then set result is expected (covers 2 case);
        else the both sides are synonym, table result is expected (covers 1 case).
    */
    auto [lhs_type, rhs_type] = rel.ValTypes();
    assert(lhs_type != ValType::kWildcard && rel.LhsValue() != "_");

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
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(),0}, {rel.RhsValue(),1} };
        shared_ptr<TableRes> table_res = std::make_shared<TableRes>(syn_to_col, table);

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

shared_ptr<ResWrapper> DataRetriever::retrieve(ProcVarRel& rel)
{
    /*
        The retrieving logic of ProcVarRel is similar to StmtVarRel.
    */
    auto [lhs_type, rhs_type] = rel.ValTypes();
    assert(lhs_type != ValType::kWildcard && rel.LhsValue() != "_");

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
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0}, {rel.RhsValue(), 1} };
        shared_ptr<TableRes> table_res = std::make_shared<TableRes>(syn_to_col, table);
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

std::shared_ptr<ResWrapper> DataRetriever::retrieve(Pattern& pat)
{
    ValType lhs_type = pat.VarValType();
    assert(lhs_type == ValType::kVarName || lhs_type == ValType::kSynonym || lhs_type == ValType::kWildcard);

    shared_ptr<unordered_set<string>> set{ nullptr };
    shared_ptr<vector<pair<string, string>>> table{ nullptr };
    if (lhs_type == ValType::kVarName) {
        set = GetPatternStmtByVar(pat);
    }
    else if (lhs_type == ValType::kSynonym)
    {
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
        unordered_map<string, int> syn_to_col = { {pat.StmtSyn(), 0}, {pat.VarName(), 1} };
        shared_ptr<TableRes> table_res = make_shared<TableRes>(syn_to_col, table);
        res = make_shared<ResWrapper>(table_res);
    }

    return res;
}

std::shared_ptr<ResWrapper> DataRetriever::retrieve(StmtStmtRel& rel)
{
    /*
        Classify LHS x RHS value type combinations by return result type
        table result:
            stmt_syn, stmt_syn -> get table of all pairs

        set result:
            stmt_syn, wildcard -> get all lhs stmt -> PENDING PKB API
            stmt_syn, stmt_num -> get all lhs stmt by rhs stmt_num
            wildcard, stmt_syn -> get all rhs stmt -> PENDING PKB API
            stmt_num, stmt_syn -> get all rhs stmt by lhs stmt_num

        bool result:
            wildcard, wildcard -> check if any relation exists -> PENDING PKB API
            wildcard, stmt_num -> get all lhs stmt by rhs stmt_num, and check set emptiness
            stmt_num, wildcard -> get all rhs stmt by lhs stmt_num, and check set emptiness
            stmt_num, stmt_num -> check relation existence
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
        if (IsSameSynonymsInvalid(rel)) {
            res = make_shared<ResWrapper>(false);
        }
        else {
            shared_ptr<vector<pair<string, string>>> table = GetAllSSRel(rel);
            unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0}, {rel.RhsValue(), 1} };
            shared_ptr<TableRes> table_res = make_shared<TableRes>(syn_to_col, table);
            res = make_shared<ResWrapper>(table_res);
        }
    }
    // Wildcard hanlding cases below
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
        if (IsSameSynonymsInvalid(rel)) {
            res = make_shared<ResWrapper>(false);
        }
        else {
            auto table = GetAllPPRel(rel);
            unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0}, {rel.RhsValue(),1} };
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
    //shared_ptr<SetRes> res = make_shared<SetRes>();
    shared_ptr<SetRes> res;
    auto ref_type = ref_ptr->GetRefType();


    unordered_set<RefType> valid_types{
            RefType::kProcRef,
            RefType::kVarRef,
            RefType::kConstRef,
            RefType::kAssignRef,
            RefType::kCallRef,
            RefType::kIfRef,
            RefType::kWhileRef,
            RefType::kReadRef,
            RefType::kPrintRef,
            RefType::kStmtRef
    };
    assert(valid_types.count(ref_type) > 0);

    shared_ptr<unordered_set<int>> int_set{ nullptr };
    shared_ptr<unordered_set<string>> str_set{ nullptr };
    if (ref_type == RefType::kProcRef) {
        str_set = pkb_ptr_->GetAllProcedures();
    }
    else if (ref_type == RefType::kVarRef) {
        str_set = pkb_ptr_->GetAllVariables();
    }
    else if (ref_type == RefType::kConstRef) {
        int_set = pkb_ptr_->GetAllConstants();
    }
    else if (ref_type == RefType::kStmtRef) {
        int_set = pkb_ptr_->GetAllStatements();
    }
    else if (ref_type == RefType::kAssignRef) {
        int_set = pkb_ptr_->GetStatementsByType(RefType::kAssignRef);
    }
    else if (ref_type == RefType::kCallRef) {
        int_set = pkb_ptr_->GetStatementsByType(RefType::kCallRef);
    }
    else if (ref_type == RefType::kIfRef) {
        int_set = pkb_ptr_->GetStatementsByType(RefType::kIfRef);
    }
    else if (ref_type == RefType::kWhileRef) {
        int_set = pkb_ptr_->GetStatementsByType(RefType::kWhileRef);
    }
    else if (ref_type == RefType::kReadRef) {
        int_set = pkb_ptr_->GetStatementsByType(RefType::kReadRef);
    }
    else if (ref_type == RefType::kPrintRef) {
        int_set = pkb_ptr_->GetStatementsByType(RefType::kPrintRef);
    }

    if (int_set != nullptr) {
        str_set = IntSetToStrSet(int_set);
    }

    string syn = ref_ptr->GetName();
    shared_ptr<SetRes> set_res = shared_ptr<SetRes>(new SetRes(syn, str_set));
    return make_shared<ResWrapper>(set_res);
}

std::shared_ptr<ResWrapper> DataRetriever::retrieve(With& with)
{
    /*
        lhs value type and rhs value type each can be one of {kInt, kString, kSynonym}
        - (int, int) -> compare value
        - (int, string) -> false
        - (int, synonym) -> get by synonym reference type and filter
        - (string, int) -> false
        - (string, string) -> compare value
        - (string, synonym) -> get by synonym reference type and filter
        - (synonym, int) -> get by synonym reference type and filter
        - (synonym, string) -> get by synonym reference type and filter
        - (synonym, synonym) -> get by synonym reference and join

        Re-group above cases as follows:
        compare value:
            - (int, int)
            - (string, string)
        false:
            - (int, string)
            - (string, int)
        set result:
            - (int, synonym)
            - (string, synonym)
            - (synonym, int)
            - (synonym, string)
        table result:
            - (synonym, synonym)
    */
    auto [lhs_type, rhs_type] = with.ValTypes();

    shared_ptr<ResWrapper> res;
    if ((lhs_type == ValType::kInt && rhs_type == ValType::kInt) || (lhs_type == ValType::kString && rhs_type == ValType::kString)) {
        bool ok = with.LhsValue() == with.RhsValue();
        res = make_shared<ResWrapper>(ok);
    }
    else if ((lhs_type == ValType::kInt && rhs_type == ValType::kString) || (lhs_type == ValType::kString && rhs_type == ValType::kInt)) {
        res = make_shared<ResWrapper>(false);
    }
    else if (lhs_type == ValType::kSynonym && rhs_type == ValType::kSynonym) {
        auto table = GetAllWithClause(with);
        unordered_map<string, int> syn_to_col = { {with.LhsValue(),0}, {with.RhsValue(),1} };
        auto table_res = make_shared<TableRes>(syn_to_col, table);
        res = make_shared<ResWrapper>(table_res);
    }
    else if (lhs_type == ValType::kSynonym) {
        auto str_val_ptr = make_shared<string>(with.RhsValue());
        auto set = GetWithClauseByRefType(with.LhsRefType(), with.RequiredLhsValType(), str_val_ptr);
        auto syn_name = with.LhsValue();
        auto set_res = make_shared<SetRes>(syn_name, set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (rhs_type == ValType::kSynonym) {
        auto str_val_ptr = make_shared<string>(with.LhsValue());
        auto set = GetWithClauseByRefType(with.RhsRefType(), with.RequiredRhsValType(), str_val_ptr);
        auto syn_name = with.RhsValue();
        auto set_res = make_shared<SetRes>(syn_name, set);
        res = make_shared<ResWrapper>(set_res);
    }

    return res;
}

bool DataRetriever::CheckSVRel(StmtVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    bool res;
    int stmt_num = rel.LhsValueAsInt().value_or(-1);
    string var_name = rel.RhsValue();
    if (type == RelType::kUsesSRel) {
        res = pkb_ptr_->CheckUses(stmt_num, var_name);
    }
    else if (type == RelType::kModifiesSRel) {
        res = pkb_ptr_->CheckModifies(stmt_num, var_name);
    }
    return res;
}

bool DataRetriever::CheckSVRelExistenceByStmt(StmtVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    shared_ptr<unordered_set<string>> set = GetVarByStmt(rel);

    return !set->empty();
}

shared_ptr<unordered_set<string>> DataRetriever::GetVarByStmt(StmtVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    int stmt_num = rel.LhsValueAsInt().value_or(-1);
    shared_ptr<unordered_set<string>> res;
    if (type == RelType::kUsesSRel) {
        res = pkb_ptr_->GetUsesVarByStmtNum(stmt_num);
    }
    else if (type == RelType::kModifiesSRel) {
        res = pkb_ptr_->GetModifiesVarByStmtNum(stmt_num);
    }
    return res;

}

shared_ptr<unordered_set<string>> DataRetriever::GetStmtByVar(StmtVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    string var_name = rel.RhsValue();
    RefType stmt_type = rel.LhsRefType();
    shared_ptr<unordered_set<int>> set;
    if (type == RelType::kUsesSRel) {
        //auto temp = pkb_ptr_->GetUsesStmtNumByVar(var_name);

        set = pkb_ptr_->GetUsesStmtNumByVar(var_name);
        set = FilterStmtSetByType(set, stmt_type);
    }
    else if (type == RelType::kModifiesSRel) {
        set = pkb_ptr_->GetModifiesStmtNumByVar(var_name);
        set = FilterStmtSetByType(set, stmt_type);
    }

    shared_ptr<unordered_set<string>> res = IntSetToStrSet(set);
    return res;
}

shared_ptr<unordered_set<string>> DataRetriever::GetStmtByWildcard(StmtVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    shared_ptr<unordered_set<int>> int_set;
    if (type == RelType::kUsesSRel) {
        int_set = pkb_ptr_->GetAllUsesStatements();
    }
    else if (type == RelType::kModifiesSRel) {
        int_set = pkb_ptr_->GetAllModifiesStatements();
    }

    return IntSetToStrSet(int_set);
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllSVRel(StmtVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    RefType lhs_stmt_type = rel.LhsRefType();
    shared_ptr<vector<pair<StmtNum, Variable>>> table;
    if (type == RelType::kUsesSRel) {
        table = pkb_ptr_->GetAllSVUses();
        table = FilterStmtTableByLhsType(table, lhs_stmt_type);
    }
    else if (type == RelType::kModifiesSRel) {
        table = pkb_ptr_->GetAllSVModifies();
        table = FilterStmtTableByLhsType(table, lhs_stmt_type);
    }
    auto res = IntStrToStrStrTable(table);
    return res;
}

bool DataRetriever::CheckPVRel(ProcVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);

    bool res;
    if (type == RelType::kUsesPRel) {
        res = pkb_ptr_->CheckUses(rel.LhsValue(), rel.RhsValue());
    }
    else if (type == RelType::kModifiesPRel) {
        res = pkb_ptr_->CheckModifies(rel.LhsValue(), rel.RhsValue());
    }
    return res;
}

bool DataRetriever::CheckPVRelExistenceByProc(ProcVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);

    shared_ptr<unordered_set<string>> set = GetVarByProc(rel);

    return !set->empty();
}

shared_ptr<unordered_set<string>> DataRetriever::GetVarByProc(ProcVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);

    string proc_name = rel.LhsValue();
    shared_ptr<unordered_set<Variable>> res;
    if (type == RelType::kUsesPRel) {
        res = pkb_ptr_->GetUsesVarByProcName(proc_name);
    }
    else if (type == RelType::kModifiesPRel) {
        res = pkb_ptr_->GetModifiesVarByProcName(proc_name);
    }

    return res;
}

shared_ptr<unordered_set<string>> DataRetriever::GetProcByVar(ProcVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);

    string var_name = rel.RhsValue();
    shared_ptr<unordered_set<string>> res;
    if (type == RelType::kUsesPRel) {
        res = pkb_ptr_->GetUsesProcNameByVar(var_name);
    }
    else if (type == RelType::kModifiesPRel) {
        res = pkb_ptr_->GetModifiesProcNameByVar(var_name);
    }
 
    return res;
}

shared_ptr<unordered_set<string>> DataRetriever::GetProcByWildcard(ProcVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);

    shared_ptr<unordered_set<Procedure>> res;
    if (type == RelType::kUsesPRel) {
        res = pkb_ptr_->GetAllUsesProcedures();
    }
    else if (type == RelType::kModifiesPRel) {
        res = pkb_ptr_->GetAllModifiesProcedures();
    }

    return res;
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllPVRel(ProcVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);

    shared_ptr<vector<pair<string, string>>> res;
    if (type == RelType::kUsesPRel) {
        res = pkb_ptr_->GetAllPVUses();
    }
    else if (type == RelType::kModifiesPRel) {
        res = pkb_ptr_->GetAllPVModifies();
    }

    return res;
}

bool DataRetriever::CheckPPRel(ProcProcRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kCallsRel || type == RelType::kCallsTRel);

    string lhs_proc_name = rel.LhsValue();
    string rhs_proc_name = rel.RhsValue();
    bool res = false;
    if (type == RelType::kCallsRel) {
        res = pkb_ptr_->CheckCalls(lhs_proc_name, rhs_proc_name);
    }
    else if (type == RelType::kCallsTRel) {
        res = pkb_ptr_->CheckCallsT(lhs_proc_name, rhs_proc_name);
    }

    return res;
}

bool DataRetriever::CheckPPRelExistence(ProcProcRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kCallsRel || type == RelType::kCallsTRel);

    bool is_empty = pkb_ptr_->IsCallsStoreEmpty();

    return !is_empty;
}

bool DataRetriever::CheckPPRelExistenceByRhsProc(ProcProcRel& rel)
{
    auto lhs_proc_set = GetLhsProcByRhsProc(rel);

    return !(lhs_proc_set->empty());
}

bool DataRetriever::CheckPPRelExistenceByLhsProc(ProcProcRel& rel)
{
    auto rhs_proc_set = GetRhsProcByLhsProc(rel);

    return !(rhs_proc_set->empty());
}

std::shared_ptr<std::unordered_set<std::string>> DataRetriever::GetRhsProcByLhsProc(ProcProcRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    string lhs_proc_name = rel.LhsValue();
    shared_ptr<unordered_set<string>> set;
    if (type == RelType::kCallsRel) {
        set = pkb_ptr_->GetCalleeFromCaller(lhs_proc_name);
    }
    else if (type == RelType::kCallsTRel) {
        set = pkb_ptr_->GetAllCalleeFromCaller(lhs_proc_name);
    }

    return set;
}

std::shared_ptr<std::unordered_set<std::string>> DataRetriever::GetRhsProcByWildcard(ProcProcRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kCallsRel || type == RelType::kCallsTRel);

    shared_ptr<unordered_set<string>> set;
    set = pkb_ptr_->GetAllCallees();

    return set;
}

std::shared_ptr<std::unordered_set<std::string>> DataRetriever::GetLhsProcByRhsProc(ProcProcRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kCallsRel || type == RelType::kCallsTRel);

    string rhs_proc_name = rel.RhsValue();
    shared_ptr<unordered_set<string>> set;
    if (type == RelType::kCallsRel) {
        set = pkb_ptr_->GetCallerFromCallee(rhs_proc_name);
    }
    else if (type == RelType::kCallsTRel) {
        set = pkb_ptr_->GetAllCallerFromCallee(rhs_proc_name);
    }

    return set;
}

std::shared_ptr<std::unordered_set<std::string>> DataRetriever::GetLhsProcByWildcard(ProcProcRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kCallsRel || type == RelType::kCallsTRel);

    string rhs_proc_name = rel.RhsValue();
    shared_ptr<unordered_set<string>> set;
    set = pkb_ptr_->GetAllCallers();

    return set;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>> DataRetriever::GetAllPPRel(ProcProcRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kCallsRel || type == RelType::kCallsTRel);

    shared_ptr<vector<StrPair>> table{ nullptr };
    if (type == RelType::kCallsRel) {
        table = pkb_ptr_->GetAllCallsRelations();
    }
    else if (type == RelType::kCallsTRel) {
        table = pkb_ptr_->GetAllCallsTRelations();
    }

    return table;
}

bool DataRetriever::CheckSSRel(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel 
        || type == RelType::kFollowsRel || type == RelType::kFollowsTRel
        || type == RelType::kNextRel || type == RelType::kNextTRel
        || type == RelType::kAffectsRel || type == RelType::kAffectsTRel);

    int lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    int rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    bool res = false;
    if (type == RelType::kParentRel) {
        res = pkb_ptr_->CheckParent(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == RelType::kParentTRel) {
        res = pkb_ptr_->CheckParentT(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == RelType::kFollowsRel) {
        res = pkb_ptr_->CheckFollows(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == RelType::kFollowsTRel) {
        res = pkb_ptr_->CheckFollowsT(lhs_stmt_num, rhs_stmt_num);
    }
    /*
    else if (type == RelType::kNextRel) {
        res = pkb_ptr_->CheckNext(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == RelType::kNextTRel) {
        res = pkb_ptr_->CheckNextT(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == RelType::kAffectsRel) {
        res = pkb_ptr_->CheckAffects(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == RelType::kAffectsTRel) {
        res = pkb_ptr_->CheckAffectsT(lhs_stmt_num, rhs_stmt_num);
    }
    */

    return res;
}

bool DataRetriever::CheckSSRelExistence(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel
        || type == RelType::kFollowsRel || type == RelType::kFollowsTRel
        || type == RelType::kNextRel || type == RelType::kNextTRel
        || type == RelType::kAffectsRel || type == RelType::kAffectsTRel);

    bool is_empty {false};
    if (type == RelType::kParentRel || type == RelType::kParentTRel) {
        is_empty = pkb_ptr_->IsParentStoreEmpty();
    }
    else if (type == RelType::kFollowsRel || type == RelType::kFollowsTRel) {
        is_empty = pkb_ptr_->IsFollowsStoreEmpty();
    }
    /*
    else if (type == RelType::kNextRel || type == RelType::kNextTRel) {
        is_empty = pkb_ptr_->IsNextStoreEmpty();
    }
    else if (type == RelType::kAffectsRel || type == RelType::kAffectsTRel) {
        is_empty = pkb_ptr_->IsAffectsStoreEmpty();
    }
    */
    

    return !is_empty;
}

bool DataRetriever::CheckSSRelExistenceByRhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel
        || type == RelType::kFollowsRel || type == RelType::kFollowsTRel
        || type == RelType::kNextRel || type == RelType::kNextTRel
        || type == RelType::kAffectsRel || type == RelType::kAffectsTRel);

    int rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    shared_ptr<unordered_set<int>> int_set = make_shared<unordered_set<int>>();
    if (type == RelType::kParentRel) {
        int_set = pkb_ptr_->GetParentFromStmt(rhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllParentsFromStmt(rhs_stmt_num, RefType::kStmtRef);
    }
    else if (type == RelType::kFollowsRel) {
        int lhs_stmt_num = pkb_ptr_->GetPredecessorStmtFromStmt(rhs_stmt_num);
        if (lhs_stmt_num != 0) {
            int_set->insert(lhs_stmt_num);
        } 
    }
    else if (type == RelType::kFollowsTRel) {
        int_set = pkb_ptr_->GetAllPredecessorStmtsFromStmt(rhs_stmt_num);
    }
    /*
    else if (type == RelType::kNextRel) {
        
    }
    else if (type == RelType::kNextTRel) {
        
    }
    else if (type == RelType::kAffectsRel) {
        
    }
    else if (type == RelType::kAffectsTRel) {
        
    }
    */

    return !int_set->empty();
}

bool DataRetriever::CheckSSRelExistenceByLhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel
        || type == RelType::kFollowsRel || type == RelType::kFollowsTRel
        || type == RelType::kNextRel || type == RelType::kNextTRel
        || type == RelType::kAffectsRel || type == RelType::kAffectsTRel);

    int lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    shared_ptr<unordered_set<int>> int_set;
    if (type == RelType::kParentRel) {
        int_set = pkb_ptr_->GetChildrenFromStmt(lhs_stmt_num, RefType::kStmtRef);  // set of immediate children
    }
    else if (type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllChildrenFromStmt(lhs_stmt_num, RefType::kStmtRef);  // set of immediate and indirect children
    }
    else if (type == RelType::kFollowsRel) {
        int rhs_stmt_num = pkb_ptr_->GetSuccessorStmtFromStmt(lhs_stmt_num);
        int_set = make_shared<unordered_set<int>>();
        if (rhs_stmt_num != 0) {
            int_set->insert(rhs_stmt_num);
        }
    }
    else if (type == RelType::kFollowsTRel) {
        int_set = pkb_ptr_->GetAllSuccessorStmtsFromStmt(lhs_stmt_num);
    }
    /*
    else if (type == RelType::kNextRel) {
        
    }
    else if (type == RelType::kNextTRel) {
        
    }
    else if (type == RelType::kAffectsRel) {
       
    }
    else if (type == RelType::kAffectsTRel) {
        
    }
    */
    return !int_set->empty();
}

std::shared_ptr<unordered_set<string>> DataRetriever::GetRhsStmtByLhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel
        || type == RelType::kFollowsRel || type == RelType::kFollowsTRel
        || type == RelType::kNextRel || type == RelType::kNextTRel
        || type == RelType::kAffectsRel || type == RelType::kAffectsTRel);

    int lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    RefType rhs_stmt_type = rel.RhsRefType();
    shared_ptr<unordered_set<int>> int_set;
    if (type == RelType::kParentRel) {
        int_set = pkb_ptr_->GetChildrenFromStmt(lhs_stmt_num, rhs_stmt_type);  // set of immediate children
    }
    else if (type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllChildrenFromStmt(lhs_stmt_num, rhs_stmt_type);  // set of immediate and indirect children
    }
    else if (type == RelType::kFollowsRel) {
        int rhs_stmt_num = pkb_ptr_->GetSuccessorStmtFromStmt(lhs_stmt_num);
        int_set = make_shared<unordered_set<int>>();
        if (rhs_stmt_num != 0) {
            int_set->insert(rhs_stmt_num);
        }
    }
    else if (type == RelType::kFollowsTRel) {
        int_set = pkb_ptr_->GetAllSuccessorStmtsFromStmt(lhs_stmt_num);
        int_set = FilterStmtSetByType(int_set, rhs_stmt_type);
    }
    /*
    else if (type == RelType::kNextRel) {
       
    }
    else if (type == RelType::kNextTRel) {
        
    }
    else if (type == RelType::kAffectsRel) {
       
    }
    else if (type == RelType::kAffectsTRel) {
       
    }
    */

    return IntSetToStrSet(int_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetRhsStmtByWildcard(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel
        || type == RelType::kFollowsRel || type == RelType::kFollowsTRel
        || type == RelType::kNextRel || type == RelType::kNextTRel
        || type == RelType::kAffectsRel || type == RelType::kAffectsTRel);

    shared_ptr<unordered_set<StmtNum>> int_set;
    if (type == RelType::kParentRel || type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllChildren();
    }
    else if (type == RelType::kFollowsRel || type == RelType::kFollowsTRel)
    {
        int_set = pkb_ptr_->GetAllSuccessorStmts();
    } 
    /*
    else if (type == RelType::kNextRel || type == RelType::kNextTRel) {
    
    }
    else if (type == RelType::kAffectsRel || type == RelType::kAffectsTRel) {

    }
    */
    

    return IntSetToStrSet(int_set);
}

std::shared_ptr<unordered_set<string>> DataRetriever::GetLhsStmtByRhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel
        || type == RelType::kFollowsRel || type == RelType::kFollowsTRel
        || type == RelType::kNextRel || type == RelType::kNextTRel
        || type == RelType::kAffectsRel || type == RelType::kAffectsTRel);

    int rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    RefType lhs_stmt_type = rel.LhsRefType();
    shared_ptr<unordered_set<int>> int_set;
    if (type == RelType::kParentRel) {
        int_set = pkb_ptr_->GetParentFromStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllParentsFromStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == RelType::kFollowsRel) {
        int lhs_stmt_num = pkb_ptr_->GetPredecessorStmtFromStmt(rhs_stmt_num);
        int_set = std::make_shared<unordered_set<int>>();
        if (lhs_stmt_num != 0) {
            int_set->insert(lhs_stmt_num);
        }
    }
    else if (type == RelType::kFollowsTRel) {
        int_set = pkb_ptr_->GetAllPredecessorStmtsFromStmt(rhs_stmt_num);
        int_set = FilterStmtSetByType(int_set, lhs_stmt_type);
    }
    /*
    else if (type == RelType::kNextRel) {

    }
    else if (type == RelType::kNextTRel) {

    }
    else if (type == RelType::kAffectsRel) {

    }
    else if (type == RelType::kAffectsTRel) {

    }
    */


    return IntSetToStrSet(int_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetLhsStmtByWildcard(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel
        || type == RelType::kFollowsRel || type == RelType::kFollowsTRel
        || type == RelType::kNextRel || type == RelType::kNextTRel
        || type == RelType::kAffectsRel || type == RelType::kAffectsTRel);

    shared_ptr<unordered_set<StmtNum>> int_set;
    if (type == RelType::kParentRel || type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllParents();
    }
    else if (type == RelType::kFollowsRel || type == RelType::kFollowsTRel)
    {
        int_set = pkb_ptr_->GetAllPredecessorStmts();
    }
    /*
    else if (type == RelType::kNextRel || type == RelType::kNextTRel) {

    }
    else if (type == RelType::kAffectsRel || type == RelType::kAffectsTRel) {

    }
    */

    return IntSetToStrSet(int_set);
}

std::shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllSSRel(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel
        || type == RelType::kFollowsRel || type == RelType::kFollowsTRel
        || type == RelType::kNextRel || type == RelType::kNextTRel
        || type == RelType::kAffectsRel || type == RelType::kAffectsTRel);

    RefType lhs_stmt_type = rel.LhsRefType();
    RefType rhs_stmt_type = rel.RhsRefType();
    shared_ptr<vector<pair<int, int>>> table;
    if (type == RelType::kParentRel) {
        table = pkb_ptr_->GetAllParentRelations();
    }
    else if (type == RelType::kParentTRel) {
        table = pkb_ptr_->GetAllParentTRelations();
    }
    else if (type == RelType::kFollowsRel) {
        table = pkb_ptr_->GetAllFollowsRelations();
    }
    else if (type == RelType::kFollowsTRel) {
        table = pkb_ptr_->GetAllFollowsTRelations();
    }
    /*
    else if (type == RelType::kNextRel) {

    }
    else if (type == RelType::kNextTRel) {

    }
    else if (type == RelType::kAffectsRel) {

    }
    else if (type == RelType::kAffectsTRel) {

    }
    */
    table = FilterStmtTableByTypes(table, lhs_stmt_type, rhs_stmt_type);

    return IntIntToStrStrTable(table);
}

std::shared_ptr<std::unordered_set<std::string>> DataRetriever::GetPatternStmtByVar(Pattern& pat)
{
    auto type = pat.GetPatternType();
    assert(type == PatternType::kAssignPattern || type == PatternType::kIfPattern || type == PatternType::kWhilePattern);
    
    shared_ptr<unordered_set<string>> set;
    if (type == PatternType::kAssignPattern) {
        set = GetAssignPatternStmtByVar(static_cast<AssignPattern&>(pat));
    }
    else if (type == PatternType::kIfPattern) {
        set = GetIfPatternStmtByVar(static_cast<IfPattern&>(pat));
    }
    else if (type == PatternType::kWhilePattern) {
        set = GetWhilePatternStmtByVar(static_cast<WhilePattern&>(pat));
    }

    return set;
}

std::shared_ptr<std::unordered_set<std::string>> DataRetriever::GetPatternStmtByWildcard(Pattern& pat)
{
    auto type = pat.GetPatternType();
    assert(type == PatternType::kAssignPattern || type == PatternType::kIfPattern || type == PatternType::kWhilePattern);

    shared_ptr<unordered_set<string>> set;
    if (type == PatternType::kAssignPattern) {
        set = GetAssignPatternStmtByWildcard(static_cast<AssignPattern&>(pat));
    }
    else if (type == PatternType::kIfPattern) {
        set = GetIfPatternStmtByWildcard(static_cast<IfPattern&>(pat));
    }
    else if (type == PatternType::kWhilePattern) {
        set = GetWhilePatternStmtByWildcard(static_cast<WhilePattern&>(pat));
    }

    return set;
}

std::shared_ptr<std::vector<std::pair<std::string, std::string>>> DataRetriever::GetAllPattern(Pattern& pat)
{
    auto type = pat.GetPatternType();
    assert(type == PatternType::kAssignPattern || type == PatternType::kIfPattern || type == PatternType::kWhilePattern);

    shared_ptr<vector<StrPair>> table;
    if (type == PatternType::kAssignPattern) {
        table = GetAllAssignPattern(static_cast<AssignPattern&>(pat));
    }
    else if (type == PatternType::kIfPattern) {
        table = GetAllIfPattern(static_cast<IfPattern&>(pat));
    }
    else if (type == PatternType::kWhilePattern) {
        table = GetAllWhilePattern(static_cast<WhilePattern&>(pat));
    }

    return table;
}

shared_ptr<unordered_set<string>> DataRetriever::GetAssignPatternStmtByVar(AssignPattern& pat)
{
    auto var_name = pat.VarName();
    shared_ptr<ExprSpec> expr_spec_ptr = pat.GetExprSpec();

    shared_ptr<unordered_set<StmtNum>> stmt_set = make_shared<unordered_set<StmtNum>>();
    if (expr_spec_ptr->IsWildcard()) {
        stmt_set = pkb_ptr_->GetModifiesStmtNumByVar(var_name);
    }
    else {
        stmt_set = pkb_ptr_->FilterByAssignPatternMatch(var_name, expr_spec_ptr);
    }

    return IntSetToStrSet(stmt_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetAssignPatternStmtByWildcard(AssignPattern& pat)
{
    shared_ptr<ExprSpec> expr_spec_ptr = pat.GetExprSpec(); 
    shared_ptr<unordered_set<StmtNum>> stmt_set = std::make_shared<unordered_set<StmtNum>>();
    if (expr_spec_ptr->IsWildcard()) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kAssignRef);
    }
    else {
        stmt_set = pkb_ptr_->FilterByAssignPatternMatch(expr_spec_ptr);
    }

    return IntSetToStrSet(stmt_set);
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllAssignPattern(AssignPattern& pat)
{
    shared_ptr<ExprSpec> expr_spec_ptr = pat.GetExprSpec();
    shared_ptr<vector<pair<StmtNum, Variable>>> stmt_var_table = pkb_ptr_->GetAssignPatternMatch(expr_spec_ptr);

    return IntStrToStrStrTable(stmt_var_table);
}

shared_ptr<unordered_set<string>> DataRetriever::GetIfPatternStmtByVar(IfPattern& pat)
{
    // TODO: plug in PKB API here
    return nullptr;
}

shared_ptr<unordered_set<string>> DataRetriever::GetIfPatternStmtByWildcard(IfPattern& pat)
{
    // TODO: plug in PKB API here
    return nullptr;
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllIfPattern(IfPattern& pat)
{
    // TODO: plug in PKB API here
    return nullptr;
}

shared_ptr<unordered_set<string>> DataRetriever::GetWhilePatternStmtByVar(WhilePattern& pat)
{
    // TODO: plug in PKB API here
    return nullptr;
}

shared_ptr<unordered_set<string>> DataRetriever::GetWhilePatternStmtByWildcard(WhilePattern& pat)
{
    // TODO: plug in PKB API here
    return nullptr;
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllWhilePattern(WhilePattern& pat)
{
    // TODO: plug in PKB API here
    return nullptr;
}

std::shared_ptr<std::unordered_set<string>> DataRetriever::GetWithClauseByRefType(RefType syn_ref_type, ValType req_val_type, shared_ptr<string> filter_val)
{
    shared_ptr<unordered_set<string>> str_set{ nullptr };
    shared_ptr<unordered_set<int>> int_set{ nullptr };

    if (syn_ref_type == RefType::kProcRef)
    {
        str_set = pkb_ptr_->GetAllProcedures();
    }
    else if (syn_ref_type == RefType::kVarRef) {
        str_set = pkb_ptr_->GetAllVariables();
    }
    else if (syn_ref_type == RefType::kConstRef) {
        int_set = pkb_ptr_->GetAllConstants();
    }
    else if (syn_ref_type == RefType::kStmtRef) {
        int_set = pkb_ptr_->GetAllStatements();
    }
    else if (syn_ref_type == RefType::kIfRef) {
        int_set = pkb_ptr_->GetStatementsByType(RefType::kIfRef);
    }
    else if (syn_ref_type == RefType::kWhileRef) {
        int_set = pkb_ptr_->GetStatementsByType(RefType::kWhileRef);
    }
    else if (syn_ref_type == RefType::kAssignRef) {
        int_set = pkb_ptr_->GetStatementsByType(RefType::kAssignRef);
    }
    else if (syn_ref_type == RefType::kReadRef) {
        if (req_val_type == ValType::kVarName) {
            str_set = pkb_ptr_->GetAllModifiesSVariables();
        }
        else if (req_val_type == ValType::kLineNum) {
            int_set = pkb_ptr_->GetStatementsByType(RefType::kReadRef);
        }

    }
    else if (syn_ref_type == RefType::kPrintRef) {
        if (req_val_type == ValType::kVarName) {
            str_set = pkb_ptr_->GetAllUsesSVariables();
        }
        else if (req_val_type == ValType::kLineNum) {
            int_set = pkb_ptr_->GetStatementsByType(RefType::kPrintRef);
        }
    }
    else if (syn_ref_type == RefType::kCallRef) {
        if (req_val_type == ValType::kVarName) {
            str_set = pkb_ptr_->GetAllCallees();
        }
        else if (req_val_type == ValType::kLineNum) {
            int_set = pkb_ptr_->GetStatementsByType(RefType::kCallRef);
        }
    }

    if (int_set != nullptr) {
        str_set = IntSetToStrSet(int_set);
    }
    if (filter_val != nullptr) {
        str_set = FilterSetByValue(str_set, *filter_val);
    }
    
    return str_set;
}

std::shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllWithClause(With& with)
{
    auto set1 = GetWithClauseByRefType(with.LhsRefType(), with.RequiredLhsValType(), nullptr);
    auto set2 = GetWithClauseByRefType(with.RhsRefType(), with.RequiredRhsValType(), nullptr);

    auto table = make_shared<vector<pair<string, string>>>();
    if (set1->size() > set2->size()) {
        auto temp_ptr = set1;
        set1 = set2;
        set2 = temp_ptr;
    }

    for (auto& value : *set1) {
        if (set2->find(value) != set2->end()) {
            table->push_back(make_pair(value, value));
        }
    }

    return table;

}

shared_ptr<unordered_set<string>> DataRetriever::IntSetToStrSet(shared_ptr<unordered_set<int>> set)
{
    auto res = make_shared<unordered_set<string>>();
    for (auto iter = set->begin(); iter != set->end(); ++iter) {
        res->insert(std::to_string(*iter));
    }

    return res;
}

std::shared_ptr<vector<pair<string, string>>> DataRetriever::IntStrToStrStrTable(std::shared_ptr<vector<pair<int, string>>> table)
{
    auto res = make_shared<vector<pair<string, string>>>();
    for (auto iter = table->begin(); iter != table->end(); ++iter) {
        auto& [k1, k2] = *iter;
        res->push_back(std::make_pair(std::to_string(k1), k2));
    }

    return res;
}

std::shared_ptr<vector<pair<string, string>>> DataRetriever::IntIntToStrStrTable(std::shared_ptr<vector<pair<int, int>>> table)
{
    auto res = make_shared<vector<pair<string, string>>>();
    for (auto iter = table->begin(); iter != table->end(); ++iter) {
        auto& [k1, k2] = *iter;
        res->push_back(std::make_pair(std::to_string(k1), std::to_string(k2)));
    }

    return res;
}

bool DataRetriever::IsSameSynonymsInvalid(StmtStmtRel& rel)
{
    if (rel.LhsValue() != rel.RhsValue()) {
        return false;
    }
    
    auto rel_type = rel.GetRelType();
    if (rel_type == RelType::kNextTRel || rel_type == RelType::kAffectsRel || rel_type == RelType::kAffectsTRel) {
        // Exceptions that can have same synonym on both sides.
        return false;
    }

    return true;
}

bool DataRetriever::IsSameSynonymsInvalid(ProcProcRel& rel)
{
    if (rel.LhsValue() != rel.RhsValue()) {
        return false;
    }

    return true;
}

shared_ptr<unordered_set<int>> DataRetriever::FilterStmtSetByType(shared_ptr<unordered_set<int>> stmts, RefType stmt_type)
{
    if (stmt_type == RefType::kStmtRef) {
        return stmts;
    }

    auto res = make_shared<unordered_set<int>>();

    for (auto iter = stmts->begin(); iter != stmts->end(); ++iter) {
        if (*(pkb_ptr_->GetStatementType(*iter)) == stmt_type) {
            res->insert(*iter);
        }
    }

    return res;
}

shared_ptr<vector<pair<int, int>>> DataRetriever::FilterStmtTableByTypes(shared_ptr<vector<pair<int, int>>> table, RefType lhs_stmt_type, RefType rhs_stmt_type)
{
    if (lhs_stmt_type == RefType::kStmtRef && rhs_stmt_type == RefType::kStmtRef) {
        return table;
    }

    shared_ptr<vector<pair<int, int>>> res;
    if (lhs_stmt_type != RefType::kStmtRef && rhs_stmt_type != RefType::kStmtRef) {
        auto lhs_type_predicate = [this, lhs_stmt_type](int stmt) -> bool { 
            auto type_ptr = this->pkb_ptr_->GetStatementType(stmt);
            return type_ptr != nullptr && *type_ptr == lhs_stmt_type; 
        };
        auto rhs_type_predicate = [this, rhs_stmt_type](int stmt) -> bool { 
            auto type_ptr = this->pkb_ptr_->GetStatementType(stmt);
            return type_ptr != nullptr && *type_ptr == rhs_stmt_type;
        };

        res = make_shared<vector<pair<int, int>>>();

        for (auto iter = table->begin(); iter != table->end(); ++iter) {
            if (lhs_type_predicate(iter->first) && rhs_type_predicate(iter->second)) {
                res->push_back(*iter);
            }
        }
    }
    else if (lhs_stmt_type != RefType::kStmtRef) {
        res = FilterStmtTableByLhsType(table, lhs_stmt_type);
    }
    else if (rhs_stmt_type != RefType::kStmtRef) {
        res = FilterStmtTableByRhsType(table, rhs_stmt_type);
    }
    
    return res;
}



