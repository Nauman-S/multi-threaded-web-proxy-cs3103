#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../../SPA/QPS/parser/QueryBuilder.h"
#include "../../SPA/QPS/clause/clauseGroup.h"
#include "../../SPA/QPS/clause/relation/FollowsRel.h"
#include "../../SPA/QPS/clause/relation/FollowsTRel.h"
#include "../../SPA/QPS/clause/relation/AffectsRel.h"
#include "../../SPA/QPS/clause/relation/AffectsTRel.h"
#include "../../SPA/QPS/optimization/ClauseSorter.h"
#include "../../SPA/QPS/reference/Ref.h"
#include "../../SPA/QPS/reference/StmtRef.h"
#include "../../SPA/QPS/reference/EntityRef.h"
#include "../../SPA/Utils/error/SyntaxError.h"
#include "../../SPA/Utils/error/SemanticError.h"
#include "../../SPA/QPS/query_result/table/Table.h"

using std::vector;
using std::string;
using std::shared_ptr;
using std::make_shared;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
    TEST_CLASS(TestTableClass) {
public:
    TEST_METHOD(BasicCrossProductJoin) {
        vector<string> left_fields = { "a", "b" };
        vector<string> right_fields = { "c", "d" };

        vector<vector<string>> left_rows = {
            {"1", "2"},
            {"4", "5"},
        };
        vector<vector<string>> right_rows = {
            {"x", "8"},
            {"y", "7"},
        };
        shared_ptr<Table> left_table = std::make_shared<Table>(left_fields, left_rows);
        shared_ptr<Table> right_table = std::make_shared<Table>(right_fields, right_rows);
        shared_ptr<Table> join_table = left_table->Join(right_table);

        vector<string> expected_first_row = { "1", "2", "x", "8" };

        Assert::AreEqual(join_table->GetNumOfRows(), 4);

        Assert::IsTrue(join_table->GetRows().at(0) == expected_first_row);
    }

    TEST_METHOD(BasicEqualJoin) {
        vector<string> left_fields = { "a", "b" };
        vector<string> right_fields = { "c", "b" };

        vector<vector<string>> left_rows = {
            {"1", "2"},
            {"4", "5"},
        };
        vector<vector<string>> right_rows = {
            {"x", "2"},
            {"y", "6"},
        };
        shared_ptr<Table> left_table = std::make_shared<Table>(left_fields, left_rows);
        shared_ptr<Table> right_table = std::make_shared<Table>(right_fields, right_rows);
        shared_ptr<Table> join_table = left_table->Join(right_table);

        vector<string> expected_first_row = { "1", "2", "x" };

        Assert::AreEqual(join_table->GetNumOfRows(), 1);

        Assert::IsTrue(join_table->GetRows().at(0) == expected_first_row);
    }
    };
    
    TEST_CLASS(TestClauseSorter) {
public:
    ClauseSorter clause_sorter;

    TEST_METHOD(TwoClause) {
        string syn_name1 = "a";
        string syn_name2 = "b";

        shared_ptr<StmtRef> ref1 = std::dynamic_pointer_cast<StmtRef>(EntityRef::CreateReference(EntityRef::kStmt, syn_name1));
        shared_ptr<StmtRef> ref2 = std::dynamic_pointer_cast<StmtRef>(EntityRef::CreateReference(EntityRef::kStmt, syn_name2));

        // priority score: 80
        shared_ptr<FollowsTRel> followsTRel = make_shared<FollowsTRel>(ref1, ref2);
        // priority score: 10
        shared_ptr<FollowsRel> followsRel = make_shared<FollowsRel>(ref1, ref2);

        vector<shared_ptr<Clause>> clauses;
        clauses.push_back(followsTRel);
        clauses.push_back(followsRel);

        shared_ptr<ClauseGroup> clause_group = make_shared<ClauseGroup>(clauses);

        shared_ptr<ClauseGroup> optimized_clause_group = clause_sorter.SortClausesInGroup(clause_group);

        Assert::IsTrue(optimized_clause_group->GetClauses().size() == 2);
        Assert::IsTrue(optimized_clause_group->GetClauses()[0] == followsRel);
        Assert::IsTrue(optimized_clause_group->GetClauses()[1] == followsTRel);
    }

    TEST_METHOD(ThreeClause) {
        string syn_name1 = "a";
        string syn_name2 = "b";
        string syn_name3 = "c";
        string syn_name4 = "d";

        shared_ptr<StmtRef> ref1 = std::dynamic_pointer_cast<StmtRef>(EntityRef::CreateReference(EntityRef::kStmt, syn_name1));
        shared_ptr<StmtRef> ref2 = std::dynamic_pointer_cast<StmtRef>(EntityRef::CreateReference(EntityRef::kStmt, syn_name2));
        shared_ptr<StmtRef> ref3 = std::dynamic_pointer_cast<StmtRef>(EntityRef::CreateReference(EntityRef::kStmt, syn_name3));
        shared_ptr<StmtRef> ref4 = std::dynamic_pointer_cast<StmtRef>(EntityRef::CreateReference(EntityRef::kStmt, syn_name3));


        // priority score: 80
        shared_ptr<FollowsTRel> followsTRel = make_shared<FollowsTRel>(ref1, ref2);
        // priority score: 10
        shared_ptr<FollowsRel> followsRel = make_shared<FollowsRel>(ref3, ref4);
        // priority score: 100
        shared_ptr<AffectsTRel> affectsTRel = make_shared<AffectsTRel>(ref3, ref2);

        vector<shared_ptr<Clause>> clauses;
        clauses.push_back(affectsTRel);
        clauses.push_back(followsTRel);
        clauses.push_back(followsRel);

        shared_ptr<ClauseGroup> clause_group = make_shared<ClauseGroup>(clauses);

        shared_ptr<ClauseGroup> optimized_clause_group = clause_sorter.SortClausesInGroup(clause_group);

        // followsRel will be the first because it has the smallest priority score.
        // Although followsTRel has higher priority than affectsTRel,
        // it is after affectsTRel because affectsTRel is connected with followsRel
        Assert::IsTrue(optimized_clause_group->GetClauses().size() == 3);
        Assert::IsTrue(optimized_clause_group->GetClauses()[0] == followsRel);
        Assert::IsTrue(optimized_clause_group->GetClauses()[1] == affectsTRel);
        Assert::IsTrue(optimized_clause_group->GetClauses()[2] == followsTRel);
    }

    };

}