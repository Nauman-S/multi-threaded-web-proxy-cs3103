#include "DataRetriever.h"

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cassert>

#include "pattern/Pattern.h"
#include "relation/StmtVarRel.h"
#include "relation/ProcVarRel.h"
#include "relation/StmtStmtRel.h"
#include "relation/UsesSRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/RelType.h"
#include "reference/ValType.h"
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

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllSVRel(StmtVarRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    RefType lhs_stmt_type = rel.LhsRefType();
    shared_ptr<vector<pair<StmtNum, Variable>>> table;
    if (type == RelType::kUsesSRel) {
        table = pkb_ptr_->GetAllSVUses();
        table = FilterStmtTableByType(table, lhs_stmt_type);
    }
    else if (type == RelType::kModifiesSRel) {
        table = pkb_ptr_->GetAllSVModifies();
        table = FilterStmtTableByType(table, lhs_stmt_type);
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

bool DataRetriever::CheckSSRel(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    int lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    int rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    bool res = false;
    if (type == RelType::kParentRel) {
        // res = pkb_ptr_->CheckParent(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == RelType::kParentTRel) {
        // res = pkb_ptr_->CheckParentT(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == RelType::kFollowsRel) {
        // res = pkb_ptr_->CheckFollows(lhs_stmt_num, rhs_stmt_num);
    }
    else if (type == RelType::kFollowsTRel) {
        // res = pkb_ptr_->CheckFollowsT(lhs_stmt_num, rhs_stmt_num);
    }

    return res;
}

std::shared_ptr<unordered_set<string>> DataRetriever::GetRhsStmtByLhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    int lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    RefType rhs_stmt_type = rel.RhsRefType();
    shared_ptr<unordered_set<int>> int_set;
    if (type == RelType::kParentRel) {
        // int_set = pkb_ptr_->GetParentRhsStmtByLhsStmt(lhs_stmt_num, rhs_stmt_type);
    }
    else if (type == RelType::kParentTRel) {
        // int_set = pkb_ptr_->GetParentTRhsStmtByLhsStmt(lhs_stmt_num, rhs_stmt_type);
    }
    else if (type == RelType::kFollowsRel) {
        // int_set = pkb_ptr_->GetFollowsRhsStmtByLhsStmt(lhs_stmt_num, rhs_stmt_type);
    }
    else if (type == RelType::kFollowsTRel) {
        // int_set = pkb_ptr_->GetFollowsTRhsStmtByLhsStmt(lhs_stmt_num, rhs_stmt_type);
    }

    return IntSetToStrSet(int_set);
}

std::shared_ptr<unordered_set<string>> DataRetriever::GetLhsStmtByRhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    int rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    RefType lhs_stmt_type = rel.LhsRefType();
    shared_ptr <unordered_set<int>> int_set;
    if (type == RelType::kParentRel) {
        // int_set = pkb_ptr_->GetParentLhsStmtByRhsStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == RelType::kParentTRel) {
        // int_set = pkb_ptr_->GetParentTLhsStmtByRhsStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == RelType::kFollowsRel) {
        // int_set = pkb_ptr_->GetFollowsLhsStmtByRhsStmt(rhs_stmt_num, lhs_stmt_type);
    }
    else if (type == RelType::kFollowsTRel) {
        // int_set = pkb_ptr_->GetFollowsTLhsStmtByRhsStmt(rhs_stmt_num, lhs_stmt_type);
    }

    return IntSetToStrSet(int_set);
}

std::shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllSSRel(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    RefType lhs_stmt_type = rel.LhsRefType();
    RefType rhs_stmt_type = rel.RhsRefType();
    shared_ptr<vector<pair<int, int>>> table;
    if (type == RelType::kParentRel) {
        // table = pkb_ptr_->GetAllSSParent(lhs_stmt_type, rhs_stmt_type);
    }
    else if (type == RelType::kParentTRel) {
        // table = pkb_ptr_->GetAllSSParentT(lhs_stmt_type, rhs_stmt_type);
    }
    else if (type == RelType::kFollowsRel) {
        // table = pkb_ptr_->GetAllSSFollows(lhs_stmt_type, rhs_stmt_type);
    }
    else if (type == RelType::kFollowsTRel) {
        // table = pkb_ptr_->GetAllSSFollowsT(lhs_stmt_type, rhs_stmt_type);
    }
    
    return IntIntToStrStrTable(table);
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

shared_ptr<unordered_set<int>> DataRetriever::FilterStmtSetByType(shared_ptr<unordered_set<int>> stmts, RefType stmt_type)
{
    shared_ptr<unordered_set<int>> res;

    for (auto iter = stmts->begin(); iter != stmts->end(); ++iter) {
        if (pkb_ptr_->GetStatementType(*iter) == stmt_type) {
            res->insert(*iter);
        }
    }

    return res;
}

shared_ptr<vector<pair<int, string>>> DataRetriever::FilterStmtTableByType(shared_ptr<vector<pair<int, string>>> table, RefType stmt_type)
{
    shared_ptr<vector<pair<int, string>>> res;
    auto type_predicate = [this, stmt_type] (int stmt) -> bool { return this->pkb_ptr_->GetStatementType(stmt) == stmt_type; };
    
    for (auto iter=table->begin(); iter != table->end(); ++iter) {
        if (type_predicate(iter->first)) {
            res->push_back(*iter);
        }
    }

    return res;
}

shared_ptr<vector<pair<int, int>>> DataRetriever::FilterStmtTableByType(shared_ptr<vector<pair<int, int>>> table, RefType lhs_stmt_type, RefType rhs_stmt_type)
{
    shared_ptr<vector<pair<int, int>>> res;
    auto lhs_type_predicate = [this, lhs_stmt_type](int stmt) -> bool { return this->pkb_ptr_->GetStatementType(stmt) == lhs_stmt_type; };
    auto rhs_type_predicate = [this, rhs_stmt_type](int stmt) -> bool { return this->pkb_ptr_->GetStatementType(stmt) == rhs_stmt_type; };

    for (auto iter = table->begin(); iter != table->end(); ++iter) {
        if (lhs_type_predicate(iter->first) && rhs_type_predicate(iter->second)) {
            res->push_back(*iter);
        }
    }

    return res;
}

std::shared_ptr<ResWrapper> DataRetriever::retrieve(StmtVarRel& rel)
{
    auto [lhs_type, rhs_type] = rel.ValTypes();
    
    std::shared_ptr<ResWrapper> res;
    if (lhs_type == ValType::kLineNum && rhs_type == ValType::kVarName) {
        bool ok = CheckSVRel(rel);
        res = std::make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kLineNum) {
        // rhs_type is kSynonym or kWildcard
        shared_ptr<unordered_set<string>> set = GetVarByStmt(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.RhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }
    else if (rhs_type == ValType::kVarName) {
        // lhs_type is kSynonym or kWildcard
        shared_ptr<unordered_set<string>> set = GetStmtByVar(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.LhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }
    else {
        // Both are kSynonym or kWildcard
        shared_ptr<vector<pair<string, string>>> table = GetAllSVRel(rel);
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(),0}, {rel.RhsValue(),1} };
        shared_ptr<TableRes> table_res = std::make_shared<TableRes>(syn_to_col, table);

        res = std::make_shared<ResWrapper>(table_res);
    }
    return res;
}

shared_ptr<ResWrapper> DataRetriever::retrieve(ProcVarRel& rel)
{
    auto [lhs_type, rhs_type] = rel.ValTypes();

    std::shared_ptr<ResWrapper> res;
    if (lhs_type == ValType::kProcName && rhs_type == ValType::kVarName) {
        bool ok = CheckPVRel(rel);
        res = std::make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kProcName) {
        shared_ptr<unordered_set<string>> set = GetVarByProc(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.RhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }
    else if (rhs_type == ValType::kVarName) {
        shared_ptr<unordered_set<string>> set = GetProcByVar(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.LhsValue(), set);
        res = std::make_shared<ResWrapper>(set_res);
    }
    else {
        // Both are kSynonym or kWildcard
        shared_ptr<vector<pair<string, string>>> table = GetAllPVRel(rel);
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0}, {rel.RhsValue(), 1} };
        shared_ptr<TableRes> table_res = std::make_shared<TableRes>(syn_to_col, table);
        res = std::make_shared<ResWrapper>(table_res);
    }
    return res;
}

std::shared_ptr<ResWrapper> DataRetriever::retrieve(Pattern& pat)
{
    ValType lhs_type = pat.LhsValType();
    shared_ptr<ExprSpec> expr_spec_ptr = pat.RhsExprSpec();

    shared_ptr<ResWrapper> res;
    if (lhs_type == ValType::kSynonym) {
        // shared_ptr<vector<pair<int, string>>> assign_var_table = pkb_ptr_->GetAllPattern(expr_spec_ptr);
        // auto table = IntStrToStrStrTable(assign_var_table);
        // unordered_map<string, int> syn_to_col = { {pat.AssignStmtSyn(), 0}, {pat.LhsValue(), 1} };
        // res = make_shared<ResWrapper>(syn_to_col, table);
    }
    else {
        // lhs type is kLineNum or kWildcard
        string var_name = pat.LhsValue();
        // shared_ptr<unordered_set<int>> assign_set = pkb_ptr_->GetPatternAssignByVar(var_name, expr_spec_ptr)
        // auto set = IntSetToStrSet(assign_set);
        // res = make_shared<ResWrapper>(var_name, set);
    }

    return res;
}

std::shared_ptr<ResWrapper> DataRetriever::retrieve(StmtStmtRel& rel)
{
    auto [lhs_type, rhs_type] = rel.ValTypes();

    shared_ptr<ResWrapper> res;
    if (lhs_type == ValType::kLineNum && rhs_type == ValType::kLineNum) {
        bool ok = CheckSSRel(rel);
        res = make_shared<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kLineNum) {
        shared_ptr<unordered_set<string>> set = GetRhsStmtByLhsStmt(rel);
        shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.RhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else if (rhs_type == ValType::kLineNum) {
        shared_ptr<unordered_set<string>> set = GetLhsStmtByRhsStmt(rel);
        shared_ptr<SetRes> set_res = make_shared<SetRes>(rel.LhsValue(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else {
        shared_ptr<vector<pair<string, string>>> table = GetAllSSRel(rel);
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0}, {rel.RhsValue(), 1} };
        shared_ptr<TableRes> table_res = make_shared<TableRes>(syn_to_col, table);
        res = make_shared<ResWrapper>(table_res);
    }
    return res;
}

shared_ptr<ResWrapper> DataRetriever::retrieve(shared_ptr<Ref> ref_ptr) {    
    //shared_ptr<SetRes> res = make_shared<SetRes>();
    shared_ptr<SetRes> res;
    auto ref_type = ref_ptr->GetRefType();


    unordered_set<RefType> valid_types {
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


