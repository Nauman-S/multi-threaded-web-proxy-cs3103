#include "DataRetriever.h"

#include <memory>
#include <cassert>

#include "relation/StmtVarRel.h"
#include "relation/ProcVarRel.h"
#include "relation/StmtStmtRel.h"
#include "relation/UsesSRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/RelType.h"
#include "reference/ValType.h"
#include "../PKB/ReadPKBManager.h"

using std::shared_ptr;
using std::make_shared;

bool DataRetriever::CheckSVRel(StmtVarRel rel)
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

shared_ptr<unordered_set<string>> DataRetriever::GetVarByStmt(StmtVarRel rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    int stmt_num = rel.LhsValueAsInt().value_or(-1);
    shared_ptr<unordered_set<string>> res;
    if (type == RelType::kUsesSRel) {
        res = make_shared<unordered_set<string>>(pkb_ptr_->GetUsesVarByStmtNum(stmt_num));
    }
    else if (type == RelType::kModifiesSRel) {
        res = make_shared<unordered_set<string>>(pkb_ptr_->GetModifiesVarByStmtNum(stmt_num));
    }
    return res;

}

shared_ptr<unordered_set<string>> DataRetriever::GetStmtByVar(StmtVarRel rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    string var_name = rel.RhsValue();
    shared_ptr<unordered_set<int>> set;
    if (type == RelType::kUsesSRel) {
        // TODO: Ask PKB side to change return res to shared_ptr
        set = make_shared<unordered_set<int>>(pkb_ptr_->GetUsesStmtNumByVar(var_name));
    }
    else if (type == RelType::kModifiesSRel) {
        // TODO: Ask PKB side to change return res to shared_ptr
        set = make_shared<unordered_set<int>>(pkb_ptr_->GetModifiesStmtNumByVar(var_name));
    }

    shared_ptr<unordered_set<string>> res = IntSetToStrSet(set);
    return res;
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllSVRel(StmtVarRel rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);

    vector<pair<int, string>> table;
    if (type == RelType::kUsesSRel) {
        table = pkb_ptr_->GetAllSVUses();
    }
    else if (type == RelType::kModifiesSRel) {
        table = pkb_ptr_->GetAllSVModifies();
    }
    auto res = IntStrToStrStrTable(table);
    return res;
}

bool DataRetriever::CheckPVRel(ProcVarRel rel)
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

shared_ptr<unordered_set<string>> DataRetriever::GetVarByProc(ProcVarRel rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);

    string proc_name = rel.LhsValue();
    shared_ptr<unordered_set<string>> res;
    if (type == RelType::kUsesPRel) {
        res = make_shared<unordered_set<string>>(pkb_ptr_->GetUsesVarByProcName(proc_name));
    }
    else if (type == RelType::kModifiesPRel) {
        res = make_shared<unordered_set<string>>(pkb_ptr_->GetModifiesVarByProcName(proc_name));
    }

    return res;
}

shared_ptr<unordered_set<string>> DataRetriever::GetProcByVar(ProcVarRel rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);

    string var_name = rel.RhsValue();
    shared_ptr<unordered_set<string>> res;
    if (type == RelType::kUsesPRel) {
        res = make_shared<unordered_set<string>>(pkb_ptr_->GetUsesProcNameByVar(var_name));
    }
    else if (type == RelType::kModifiesPRel) {
        res = make_shared<unordered_set<string>>(pkb_ptr_->GetModifiesProcNameByVar(var_name));
    }

    return res;
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllPVRel(ProcVarRel rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);

    shared_ptr<vector<pair<string, string>>> res;
    if (type == RelType::kUsesPRel) {
        res = make_shared<vector<pair<string, string>>>(pkb_ptr_->GetAllPVUses());
    }
    else if (type == RelType::kModifiesPRel) {
        res = make_shared<vector<pair<string, string>>>(pkb_ptr_->GetAllPVModifies());
    }

    return res;
}

shared_ptr<unordered_set<string>> DataRetriever::IntSetToStrSet(shared_ptr<unordered_set<int>> set)
{
    auto res = make_shared<unordered_set<string>>();
    for (auto iter = set->begin(); iter != set->end(); ++iter) {
        res->insert(std::to_string(*iter));
    }

    return res;
}

std::shared_ptr<vector<pair<string, string>>> DataRetriever::IntStrToStrStrTable(vector<pair<int, string>> table)
{
    auto res = make_shared<vector<pair<string, string>>>();
    for (auto& [k1, k2]:table) {
        res->push_back(std::make_pair(std::to_string(k1), k2));
    }

    return res;
}

std::shared_ptr<ResWrapper> DataRetriever::retrieve(StmtVarRel rel)
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

shared_ptr<ResWrapper> DataRetriever::retrieve(ProcVarRel rel)
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


