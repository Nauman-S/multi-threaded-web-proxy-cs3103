#include "DataRetriever.h"

#include <memory>
#include <cassert>

#include "relation/StmtVarRel.h"
#include "relation/UsesSRel.h"
#include "relation/ModifiesSRel.h"
#include "relation/RelType.h"
#include "reference/ValType.h"

bool DataRetriever::CheckSVRel(StmtVarRel rel)
{
    // TODO: Add PKB API calls here
    RelType type = rel.GetRelType();

    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);
    if (type == RelType::kUsesSRel) {

    }
    else if (type == RelType::kModifiesSRel) {

    }
}

unordered_set<string>& DataRetriever::GetVarByStmt(StmtVarRel rel)
{

    // TODO: Add PKB API calls here
    RelType type = rel.GetRelType();

    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);
    if (type == RelType::kUsesSRel) {
        
    }
    else if (type == RelType::kModifiesSRel) {

    }

}

unordered_set<string>& DataRetriever::GetStmtByVar(StmtVarRel rel)
{
    // TODO: Add PKB API calls here
    RelType type = rel.GetRelType();

    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);
    if (type == RelType::kUsesSRel) {

    }
    else if (type == RelType::kModifiesSRel) {

    }
}

const vector<pair<string, string>>& DataRetriever::GetAllSVRel(StmtVarRel rel)
{
    // TODO: Add PKB API calls here
    RelType type = rel.GetRelType();

    assert(type == RelType::kUsesSRel || type == RelType::kModifiesSRel);
    if (type == RelType::kUsesSRel) {

    }
    else if (type == RelType::kModifiesSRel) {

    }
}

bool DataRetriever::CheckPVRel(ProcVarRel rel)
{
    // TODO: Add PKB API calls here
    RelType type = rel.GetRelType();

    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);
    if (type == RelType::kUsesPRel) {

    }
    else if (type == RelType::kModifiesPRel) {

    }
}

unordered_set<string>& DataRetriever::GetVarByProc(ProcVarRel rel)
{
    // TODO: Add PKB API calls here
    RelType type = rel.GetRelType();

    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);
    if (type == RelType::kUsesPRel) {

    }
    else if (type == RelType::kModifiesPRel) {

    }
}

unordered_set<string>& DataRetriever::GetProcByVar(ProcVarRel rel)
{
    // TODO: Add PKB API calls here
    RelType type = rel.GetRelType();

    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);
    if (type == RelType::kUsesPRel) {

    }
    else if (type == RelType::kModifiesPRel) {

    }
}

const vector<pair<string, string>>& DataRetriever::GetAllPVRel(ProcVarRel rel)
{
    // TODO: Add PKB API calls here
    RelType type = rel.GetRelType();

    assert(type == RelType::kUsesPRel || type == RelType::kModifiesPRel);
    if (type == RelType::kUsesPRel) {

    }
    else if (type == RelType::kModifiesPRel) {

    }
}

std::unique_ptr<ResWrapper> DataRetriever::retrieve(StmtVarRel rel)
{
    auto [lhs_type, rhs_type] = rel.ValTypes();
    
    std::unique_ptr<ResWrapper> res;
    if (lhs_type == ValType::kLineNum && rhs_type == ValType::kVarName) {
        bool ok = CheckSVRel(rel);
        res = std::make_unique<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kLineNum) {
        // rhs_type is kSynonym or kWildcard
        unordered_set<string> set = GetVarByStmt(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.RhsValue(), set);
        res = std::make_unique<ResWrapper>(set_res);
    }
    else if (rhs_type == ValType::kVarName) {
        // lhs_type is kSynonym or kWildcard
        unordered_set<string> set = GetStmtByVar(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.LhsValue(), set);
        res = std::make_unique<ResWrapper>(set_res);
    }
    else {
        // Both are kSynonym or kWildcard
        vector<pair<string, string>> table = GetAllSVRel(rel);
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(),0}, {rel.RhsValue(),1} };
        shared_ptr<TableRes<TwoTuple>> table_res = std::make_shared<TableRes<TwoTuple>>(syn_to_col, table);
        res = std::make_unique<ResWrapper>(table_res);
    }
    return res;
}

std::unique_ptr<ResWrapper> DataRetriever::retrieve(ProcVarRel rel)
{
    auto [lhs_type, rhs_type] = rel.ValTypes();

    std::unique_ptr<ResWrapper> res;
    if (lhs_type == ValType::kProcName && rhs_type == ValType::kVarName) {
        bool ok = CheckPVRel(rel);
        res = std::make_unique<ResWrapper>(ok);
    }
    else if (lhs_type == ValType::kProcName) {
        unordered_set<string> set = GetVarByProc(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.RhsValue(), set);
        res = std::make_unique<ResWrapper>(set_res);
    }
    else if (rhs_type == ValType::kVarName) {
        unordered_set<string> set = GetProcByVar(rel);
        shared_ptr<SetRes> set_res = std::make_shared<SetRes>(rel.LhsValue(), set);
        res = std::make_unique<ResWrapper>(set_res);
    }
    else {
        // Both are kSynonym or kWildcard
        vector<pair<string, string>> table = GetAllPVRel(rel);
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(),0}, {rel.RhsValue(),1} };
        shared_ptr<TableRes<TwoTuple>> table_res = std::make_shared<TableRes<TwoTuple>>(syn_to_col, table);
        res = std::make_unique<ResWrapper>(table_res);
    }
    return res;
}
