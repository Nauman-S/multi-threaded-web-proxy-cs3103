#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "clause/AttrType.h"
#include "clause/ClauseType.h"
#include "clause/relation/ModifiesPRel.h"
#include "clause/relation/ModifiesSRel.h"
#include "clause/relation/UsesPRel.h"
#include "clause/relation/UsesSRel.h"
#include "query_result/ResWrapper.h"
#include "query_result/SetRes.h"
#include "query_result/TableRes.h"
#include "reference/Ref.h"
#include "reference/ValType.h"
#include "optimization/ResTableCache.h"
#include "../PKB/ReadPKBManager.h"
#include "../Utils/type/TypeDef.h"
// Use forward declaration to avoid cyclic include of Visitor pattern
class StmtVarRel;
class ProcVarRel;
class StmtStmtRel;
class ProcProcRel;
class Pattern;
class AssignPattern;
class IfPattern;
class WhilePattern;
class With;


class DataRetriever {
protected:  // attributes
    std::shared_ptr<ReadPKBManager> pkb_ptr_;
    ResTableCache<StmtNum, StmtNum> stmt_stmt_table_cache_;

public:  // public API
    DataRetriever() : stmt_stmt_table_cache_{} {
        pkb_ptr_ = ReadPKBManager::GetInstance();
    };

    DataRetriever(std::shared_ptr<ReadPKBManager> pkb) : pkb_ptr_{ pkb }, stmt_stmt_table_cache_{} {
    };

    std::shared_ptr<ResWrapper> retrieve(StmtVarRel& rel);

    std::shared_ptr<ResWrapper> retrieve(ProcVarRel& rel);

    std::shared_ptr<ResWrapper> retrieve(StmtStmtRel& rel);

    std::shared_ptr<ResWrapper> retrieve(ProcProcRel& rel);

    std::shared_ptr<ResWrapper> retrieve(Pattern& pat);

    std::shared_ptr<ResWrapper> retrieve(std::shared_ptr<Ref> ref_ptr);

    std::shared_ptr<ResWrapper> retrieve(With& with);

    // Attribute selecting
    std::shared_ptr<Procedure> MapCallsStmtNumToProcName(std::string& stmt_num_str);
    std::shared_ptr<Variable> MapReadStmtNumToVarName(std::string& stmt_num_str);
    std::shared_ptr<Variable> MapPrintStmtNumToVarName(std::string& stmt_num_str);

protected:  // helper methods
    // Stmt-Var relations
    bool CheckSVRel(StmtVarRel& rel);                 // (stmt_num, var_name)
    bool CheckSVRelExistenceByStmt(StmtVarRel& rel);  // (stmt_num, wildcard)
    std::shared_ptr<std::unordered_set<std::string>> GetVarByStmt(
        StmtVarRel& rel);  // (stmt_num, synonym)
    std::shared_ptr<std::unordered_set<std::string>> GetStmtByVar(
        StmtVarRel& rel);  // (synonym, var_name)
    std::shared_ptr<std::unordered_set<std::string>> GetStmtByWildcard(
        StmtVarRel& rel);  // (synonym, wildcard)
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>> GetAllSVRel(
        StmtVarRel& rel);  // (synonym, synonym)

    // Proc-Var relations
    bool CheckPVRel(ProcVarRel& rel);                 // (proc_name, var_name)
    bool CheckPVRelExistenceByProc(ProcVarRel& rel);  // (proc_name, wildcard)
    std::shared_ptr<std::unordered_set<std::string>> GetVarByProc(
        ProcVarRel& rel);  // (proc_name, synonym)
    std::shared_ptr<std::unordered_set<std::string>> GetProcByVar(
        ProcVarRel& rel);  // (synonym, var_name)
    std::shared_ptr<std::unordered_set<std::string>> GetProcByWildcard(
        ProcVarRel& rel);  // (synonym, wildcard)
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>> GetAllPVRel(
        ProcVarRel& rel);  // (synonym, synonym)

    // Proc-Proc relations
    bool CheckPPRel(ProcProcRel& rel);           // (proc_name, proc_name)
    bool CheckPPRelExistence(ProcProcRel& rel);  // (wildcard, wildcard)
    bool CheckPPRelExistenceByRhsProc(ProcProcRel& rel);  // (wildcard, proc_name)
    bool CheckPPRelExistenceByLhsProc(ProcProcRel& rel);  // (proc_name, wildcard)
    std::shared_ptr<std::unordered_set<std::string>> GetRhsProcByLhsProc(
        ProcProcRel& rel);  // (proc_name, synonym)
    std::shared_ptr<std::unordered_set<std::string>> GetRhsProcByWildcard(
        ProcProcRel& rel);  // (wildcard, synonym)
    std::shared_ptr<std::unordered_set<std::string>> GetLhsProcByRhsProc(
        ProcProcRel& rel);  // (synonym, proc_name)
    std::shared_ptr<std::unordered_set<std::string>> GetLhsProcByWildcard(
        ProcProcRel& rel);  // (synonym, wildcard)
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>> GetAllPPRel(
        ProcProcRel& rel);  // (synonym, synonym)

    // Stmt-Stmt relations
    bool CheckSSRel(StmtStmtRel& rel);                    // (stmt_num, stmt_num)
    bool CheckSSRelExistence(StmtStmtRel& rel);           // (wildcard, wildcard)
    bool CheckSSRelExistenceByRhsStmt(StmtStmtRel& rel);  // (wildcard, stmt_num)
    bool CheckSSRelExistenceByLhsStmt(StmtStmtRel& rel);  // (stmt_num, wildcard)
    std::shared_ptr<std::unordered_set<std::string>> GetRhsStmtByLhsStmt(
        StmtStmtRel& rel);  // (stmt_num, synonym)
    std::shared_ptr<std::unordered_set<std::string>> GetRhsStmtByWildcard(
        StmtStmtRel& rel);  // (wildcard, synonym)
    std::shared_ptr<std::unordered_set<std::string>> GetLhsStmtByRhsStmt(
        StmtStmtRel& rel);  // (synonym, stmt_num)
    std::shared_ptr<std::unordered_set<std::string>> GetLhsStmtByWildcard(
        StmtStmtRel& rel);  // (synonym, wildcard)
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>> GetAllSSRel(
        StmtStmtRel& rel);  // (synonym, synonym)
    std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> GetAllSSRelFromPKB(
        ClauseType type);

    // Pattern
    std::shared_ptr<std::unordered_set<std::string>> GetPatternStmtByVar(
        Pattern& pat);  // assign_syn(var_name, ExprSpec)
    std::shared_ptr<std::unordered_set<std::string>> GetPatternStmtByWildcard(
        Pattern& pat);  // assign_syn(wildcard, ExprSpec)
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        GetAllPattern(Pattern& pat);  // assign_syn(var_syn, ExprSpec)

    // Assign Pattern
    std::shared_ptr<std::unordered_set<std::string>> GetAssignPatternStmtByVar(
        AssignPattern& pat);  // assign_syn(var_name, ExprSpec)
    std::shared_ptr<std::unordered_set<std::string>>
        GetAssignPatternStmtByWildcard(
            AssignPattern& pat);  // assign_syn(wildcard, ExprSpec)
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        GetAllAssignPattern(AssignPattern& pat);  // assign_syn(var_syn, ExprSpec)

    // If Pattern
    std::shared_ptr<std::unordered_set<std::string>> GetIfPatternStmtByVar(
        IfPattern& pat);  // assign_syn(var_name, ExprSpec)
    std::shared_ptr<std::unordered_set<std::string>> GetIfPatternStmtByWildcard(
        IfPattern& pat);  // assign_syn(wildcard, ExprSpec)
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        GetAllIfPattern(IfPattern& pat);  // assign_syn(var_syn, ExprSpec)

    // While Pattern
    std::shared_ptr<std::unordered_set<std::string>> GetWhilePatternStmtByVar(
        WhilePattern& pat);  // assign_syn(var_name, ExprSpec)
    std::shared_ptr<std::unordered_set<std::string>>
        GetWhilePatternStmtByWildcard(
            WhilePattern& pat);  // assign_syn(wildcard, ExprSpec)
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        GetAllWhilePattern(WhilePattern& pat);  // assign_syn(var_syn, ExprSpec)

    // With clause
    std::shared_ptr<std::unordered_set<std::string>>
        GetWithClauseBySingleAttrTypeRefType(RefType syn_ref_type);
    std::shared_ptr<std::unordered_set<std::string>>
        GetWithClauseByMultipleAttrTypeRefType(RefType syn_ref_type,
            AttrType attr_type,
            std::string& pivot_val);
    std::shared_ptr<std::unordered_set<std::string>>
        GetWithClauseByRefTypeAndFilterVal(RefType syn_ref_type, AttrType attr_type,
            std::string& filter_val);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        GetAllWithClause(With& with);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        GetWithClauseAttrPairs(RefType syn_ref_type);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        JoinWithClauseSets(std::shared_ptr<std::unordered_set<std::string>> set1,
            std::shared_ptr<std::unordered_set<std::string>> set2);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        JoinWithClauseSetAndTable(std::shared_ptr<std::unordered_set<std::string>> set1,
            std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table2);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        JoinWithClauseSetAndTable(std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table1,
            std::shared_ptr<std::unordered_set<std::string>> set2);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        JoinWithClauseTables(
            std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table1,
            std::shared_ptr<std::vector<std::pair<std::string, std::string>>> table2);


    // type conversion helpers
    std::shared_ptr<std::unordered_set<std::string>> StmtSetToStrSet(
        std::shared_ptr<std::unordered_set<StmtNum>> set);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        StmtNameTableToStrStrTable(
            std::shared_ptr<std::vector<std::pair<StmtNum, std::string>>> table);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        StmtptrNameptrTableToStrStrTable(
            std::shared_ptr<std::vector<std::pair<std::shared_ptr<StmtNum>, std::shared_ptr<std::string>>>> table);
    std::shared_ptr<std::vector<std::pair<std::string, std::string>>>
        StmtStmtTableToStrStrTable(std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> table);

    // type checking helpers
    bool IsSameSynonymsInvalid(StmtStmtRel& rel);
    bool IsSameSynonymsInvalid(ProcProcRel& rel);

    // Filter helpers
    std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>>
        FilterStmtTableByTypes(
            std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> table,
            RefType lhs_stmt_type, RefType rhs_stmt_type);
    std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>>
        FilterStmtTableByBothTypes(
            std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> table,
            RefType lhs_stmt_type, RefType rhs_stmt_type);

    template <typename T>
    std::shared_ptr<std::vector<std::pair<StmtNum, T>>> FilterStmtTableByLhsType(
        std::shared_ptr<std::vector<std::pair<StmtNum, T>>> table,
        RefType lhs_stmt_type) {
        if (lhs_stmt_type == RefType::kStmtRef) {
            return table;
        }

        auto res = std::make_shared<std::vector<std::pair<StmtNum, T>>>();
        for (auto iter = table->begin(); iter != table->end(); ++iter) {
            if (*(pkb_ptr_->GetStatementType(iter->first)) == lhs_stmt_type) {
                res->push_back(*iter);
            }
        }

        return res;
    }

    template <typename T>
    std::shared_ptr<std::vector<std::pair<T, StmtNum>>> FilterStmtTableByRhsType(
        std::shared_ptr<std::vector<std::pair<T, StmtNum>>> table,
        RefType rhs_stmt_type) {
        if (rhs_stmt_type == RefType::kStmtRef) {
            return table;
        }

        auto res = std::make_shared<std::vector<std::pair<T, StmtNum>>>();
        for (auto iter = table->begin(); iter != table->end(); ++iter) {
            if (*(pkb_ptr_->GetStatementType(iter->second)) == rhs_stmt_type) {
                res->push_back(*iter);
            }
        }

        return res;
    }

    template <typename T>
    std::shared_ptr<std::unordered_set<T>> FilterSetByValue(
        std::shared_ptr<std::unordered_set<T>> set, T filter_val) {
        auto res = std::make_shared<std::unordered_set<T>>();

        for (auto iter = set->begin(); iter != set->end(); ++iter) {
            if (*iter == filter_val) {
                res->insert(*iter);
            }
        }

        return res;
    }

    template <typename T>
    std::shared_ptr<std::unordered_set<T>> GetAllEqualRowValues(
        std::shared_ptr<std::vector<std::pair<T, T>>> table) {
        auto res_set = std::make_shared<std::unordered_set<T>>();
        for (auto& [val1, val2] : *table) {
            if (val1 == val2) {
                res_set->insert(val1);
            }
        }

        return res_set;
    }
};
