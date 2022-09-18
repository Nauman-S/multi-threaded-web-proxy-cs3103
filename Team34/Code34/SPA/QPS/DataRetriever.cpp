#include "DataRetriever.h"

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
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

bool DataRetriever::CheckSSRel(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

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

    return res;
}

bool DataRetriever::CheckSSRelExistence(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    bool is_empty;
    if (type == RelType::kParentRel || type == RelType::kParentTRel) {
        is_empty = pkb_ptr_->IsParentStoreEmpty();
    }
    else if (type == RelType::kFollowsRel || type == RelType::kFollowsTRel) {
        is_empty = pkb_ptr_->IsFollowsStoreEmpty();
    }

    return !is_empty;
}

bool DataRetriever::CheckSSRelExistenceByRhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    int rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    shared_ptr <unordered_set<int>> int_set;
    if (type == RelType::kParentRel) {
        int lhs_stmt_num = pkb_ptr_->GetParentFromStmt(rhs_stmt_num);
        if (lhs_stmt_num != 0) {
            int_set->insert(lhs_stmt_num);
        }
    }
    else if (type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllParentsFromStmt(rhs_stmt_num);
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

    return !int_set->empty();
}

bool DataRetriever::CheckSSRelExistenceByLhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    int lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    shared_ptr<unordered_set<int>> int_set;
    if (type == RelType::kParentRel) {
        int_set = pkb_ptr_->GetChildrenFromStmt(lhs_stmt_num);  // set of immediate children
    }
    else if (type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllChildrenFromStmt(lhs_stmt_num);  // set of immediate and indirect children
    }
    else if (type == RelType::kFollowsRel) {
        // What if no successor stmt num???
        // Discuss with PKB to return a set instead
        int rhs_stmt_num = pkb_ptr_->GetSuccessorStmtFromStmt(lhs_stmt_num);
        if (rhs_stmt_num != 0) {
            int_set->insert(rhs_stmt_num);
        }
    }
    else if (type == RelType::kFollowsTRel) {
        int_set = pkb_ptr_->GetAllSuccessorStmtsFromStmt(lhs_stmt_num);
    }

    return !int_set->empty();
}

std::shared_ptr<unordered_set<string>> DataRetriever::GetRhsStmtByLhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    int lhs_stmt_num = rel.LhsValueAsInt().value_or(-1);
    RefType rhs_stmt_type = rel.RhsRefType();
    shared_ptr<unordered_set<int>> int_set = make_shared<unordered_set<int>>();
    if (type == RelType::kParentRel) {
        int_set = pkb_ptr_->GetChildrenFromStmt(lhs_stmt_num);  // set of immediate children
        int_set = FilterStmtSetByType(int_set, rhs_stmt_type);
    }
    else if (type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllChildrenFromStmt(lhs_stmt_num);  // set of immediate and indirect children
        int_set = FilterStmtSetByType(int_set, rhs_stmt_type);
    }
    else if (type == RelType::kFollowsRel) {
        // What if no successor stmt num???
        // rhs_stmt_num will evaluate to 0
        int rhs_stmt_num = pkb_ptr_->GetSuccessorStmtFromStmt(lhs_stmt_num);
        if (rhs_stmt_num != 0) {
            int_set->insert(rhs_stmt_num);
        }
    }
    else if (type == RelType::kFollowsTRel) {
        int_set = pkb_ptr_->GetAllSuccessorStmtsFromStmt(lhs_stmt_num);
        int_set = FilterStmtSetByType(int_set, rhs_stmt_type);
    }

    return IntSetToStrSet(int_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetRhsStmtByWildcard(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    shared_ptr<unordered_set<StmtNum>> int_set;
    if (type == RelType::kParentRel || type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllChildren();
    }
    else if (type == RelType::kFollowsRel || type == RelType::kFollowsTRel)
    {
        int_set = pkb_ptr_->GetAllSuccessorStmts();
    }

    return IntSetToStrSet(int_set);
}

std::shared_ptr<unordered_set<string>> DataRetriever::GetLhsStmtByRhsStmt(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    int rhs_stmt_num = rel.RhsValueAsInt().value_or(-1);
    RefType lhs_stmt_type = rel.LhsRefType();
    shared_ptr<unordered_set<int>> int_set = std::make_shared<unordered_set<int>>();
    if (type == RelType::kParentRel) {
        int lhs_stmt_num = pkb_ptr_->GetParentFromStmt(rhs_stmt_num);
        if (lhs_stmt_num != 0) {
            int_set->insert(lhs_stmt_num);
        }
    }
    else if (type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllParentsFromStmt(rhs_stmt_num);
        int_set = FilterStmtSetByType(int_set, lhs_stmt_type);
    }
    else if (type == RelType::kFollowsRel) {
        int lhs_stmt_num = pkb_ptr_->GetPredecessorStmtFromStmt(rhs_stmt_num);
        if (lhs_stmt_num != 0) {
            int_set->insert(lhs_stmt_num);
        }
    }
    else if (type == RelType::kFollowsTRel) {
        int_set = pkb_ptr_->GetAllPredecessorStmtsFromStmt(rhs_stmt_num);
        int_set = FilterStmtSetByType(int_set, lhs_stmt_type);
    }

    return IntSetToStrSet(int_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetLhsStmtByWildcard(StmtStmtRel& rel)
{
    RelType type = rel.GetRelType();
    assert(type == RelType::kParentRel || type == RelType::kParentTRel || type == RelType::kFollowsRel || type == RelType::kFollowsTRel);

    shared_ptr<unordered_set<StmtNum>> int_set;
    if (type == RelType::kParentRel || type == RelType::kParentTRel) {
        int_set = pkb_ptr_->GetAllParents();
    }
    else if (type == RelType::kFollowsRel || type == RelType::kFollowsTRel)
    {
        int_set = pkb_ptr_->GetAllPredecessorStmts();
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
    table = FilterStmtTableByType(table, lhs_stmt_type, rhs_stmt_type);

    return IntIntToStrStrTable(table);
}

shared_ptr<unordered_set<string>> DataRetriever::GetAssignPatternStmtByVar(Pattern& pat)
{
    auto var_name = pat.LhsValue();
    shared_ptr<ExprSpec> expr_spec_ptr = pat.RhsExprSpec();

    shared_ptr<unordered_set<StmtNum>> stmt_set;
    if (expr_spec_ptr->IsWildcard()) {
        stmt_set = pkb_ptr_->GetModifiesStmtNumByVar(var_name);
    }
    else {
        shared_ptr<unordered_set<StmtNum>> temp_set = pkb_ptr_->GetModifiesStmtNumByVar(var_name);
        for (auto stmt_num : *temp_set) {
            if (pkb_ptr_->IsAssignPatternMatch(stmt_num, expr_spec_ptr)) {
                stmt_set->insert(stmt_num);
            }
        }
    }

    return IntSetToStrSet(stmt_set);
}

shared_ptr<unordered_set<string>> DataRetriever::GetAssignPatternStmtByWildcard(Pattern& pat)
{
    shared_ptr<ExprSpec> expr_spec_ptr = pat.RhsExprSpec(); 
    shared_ptr<unordered_set<StmtNum>> stmt_set;
    if (expr_spec_ptr->IsWildcard()) {
        stmt_set = pkb_ptr_->GetStatementsByType(RefType::kAssignRef);
    }
    else {
        shared_ptr<unordered_set<StmtNum>> temp_set = pkb_ptr_->GetStatementsByType(RefType::kAssignRef);
        for (auto stmt_num : *temp_set) {
            if (pkb_ptr_->IsAssignPatternMatch(stmt_num, expr_spec_ptr)) {
                stmt_set->insert(stmt_num);
            }
        }
    }

    return IntSetToStrSet(stmt_set);
}

shared_ptr<vector<pair<string, string>>> DataRetriever::GetAllAssignPattern(Pattern& pat)
{
    shared_ptr<ExprSpec> expr_spec_ptr = pat.RhsExprSpec();
    shared_ptr<vector<pair<StmtNum, Variable>>> stmt_var_table = pkb_ptr_->GetAssignPatternMatch(expr_spec_ptr);

    return IntStrToStrStrTable(stmt_var_table);
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
    if (stmt_type == RefType::kStmtRef) {
        return stmts;
    }

    auto res = make_shared<unordered_set<int>>();

    for (auto iter = stmts->begin(); iter != stmts->end(); ++iter) {
        if (*pkb_ptr_->GetStatementType(*iter) == stmt_type) {
            res->insert(*iter);
        }
    }

    return res;
}

shared_ptr<vector<pair<int, string>>> DataRetriever::FilterStmtTableByType(shared_ptr<vector<pair<int, string>>> table, RefType stmt_type)
{
    shared_ptr<vector<pair<int, string>>> res;
    auto type_predicate = [this, stmt_type] (int stmt) -> bool { return *this->pkb_ptr_->GetStatementType(stmt) == stmt_type; };
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
    auto lhs_type_predicate = [this, lhs_stmt_type](int stmt) -> bool { return *this->pkb_ptr_->GetStatementType(stmt) == lhs_stmt_type; };
    auto rhs_type_predicate = [this, rhs_stmt_type](int stmt) -> bool { return *this->pkb_ptr_->GetStatementType(stmt) == rhs_stmt_type; };

    for (auto iter = table->begin(); iter != table->end(); ++iter) {
        if (lhs_type_predicate(iter->first) && rhs_type_predicate(iter->second)) {
            res->push_back(*iter);
        }
    }

    return res;
}

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
    ValType lhs_type = pat.LhsValType();
    assert(lhs_type == ValType::kVarName || lhs_type == ValType::kSynonym || lhs_type == ValType::kWildcard);

    shared_ptr<unordered_set<string>> set { nullptr };
    shared_ptr<vector<pair<string, string>>> table { nullptr };
    if (lhs_type == ValType::kVarName) {
        set = GetAssignPatternStmtByVar(pat);
    }
    else if(lhs_type == ValType::kSynonym) 
    {
        table = GetAllAssignPattern(pat);
    }
    else if (lhs_type == ValType::kWildcard) {
        set = GetAssignPatternStmtByWildcard(pat);
    }

    shared_ptr<ResWrapper> res;
    if (set != nullptr) {
        shared_ptr<SetRes> set_res = make_shared<SetRes>(pat.AssignStmtSyn(), set);
        res = make_shared<ResWrapper>(set_res);
    }
    else {
        unordered_map<string, int> syn_to_col = { {pat.AssignStmtSyn(), 0}, {pat.LhsValue(), 1} };
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
        shared_ptr<vector<pair<string, string>>> table = GetAllSSRel(rel);
        unordered_map<string, int> syn_to_col = { {rel.LhsValue(), 0}, {rel.RhsValue(), 1} };
        shared_ptr<TableRes> table_res = make_shared<TableRes>(syn_to_col, table);
        res = make_shared<ResWrapper>(table_res);
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


