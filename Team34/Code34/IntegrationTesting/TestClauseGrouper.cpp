#include "stdafx.h"
#include "CppUnitTest.h"

#include <memory>
#include <string>
#include <iostream>

#include "../SPA/QPS/parser/QueryBuilder.h"
#include "../SPA/QPS/clause_grouper/ClauseGrouper.h"
#include "../SPA/QPS/clause_grouper/OptimizedClauseGrouper.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace IntegrationTesting {
    TEST_CLASS(TestClauseGrouper) {
    private:
        shared_ptr<QueryBuilder> query_builder_ = make_shared<QueryBuilder>();
    public:
        TEST_METHOD(NoSynClauses) {
            string query_string = "variable v; Select v such that Follows(1, 5) and Parent*(1, 5) with 2 = \"test\"";

            shared_ptr<Query> query = query_builder_->GetQuery(query_string);

            shared_ptr<ClauseGrouper> clause_grouper = make_shared<OptimizedClauseGrouper>(*(query->GetAllClauses()), query->GetSelectSynonyms());

            Assert::IsTrue(clause_grouper->GetClauseGroupWoSyn()->GetClauses().size() == 3);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWoSelectSyn().size() == 0);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWithSelectSyn().size() == 0);
        }

        TEST_METHOD(NoSynClausesAndClausesWoSelectSyn) {
            string query_string = "variable v,v1,v2,v3; stmt s1, s2, s3, s4; Select v such that Follows(1, 5) and Parent*(1, 5) with 2 = \"test\" such that Modifies(s1, v1) and Uses (s2, v2) such that Uses(s3, v3)";

            shared_ptr<Query> query = query_builder_->GetQuery(query_string);

            shared_ptr<ClauseGrouper> clause_grouper = make_shared<OptimizedClauseGrouper>(*(query->GetAllClauses()), query->GetSelectSynonyms());

            Assert::IsTrue(clause_grouper->GetClauseGroupWoSyn()->GetClauses().size() == 3);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWoSelectSyn().size() == 3);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWithSelectSyn().size() == 0);
        }

        TEST_METHOD(NoSynClausesAndClausesWoSelectSyn2) {
            string query_string = "variable v,v1,v2,v3; stmt s1, s2, s3, s4; Select v such that Follows(1, 5) and Parent*(1, 5) with 2 = \"test\" such that Modifies(s2, v1) and Uses (s2, v2) such that Uses(s3, v3)";

            shared_ptr<Query> query = query_builder_->GetQuery(query_string);

            shared_ptr<ClauseGrouper> clause_grouper = make_shared<OptimizedClauseGrouper>(*(query->GetAllClauses()), query->GetSelectSynonyms());

            Assert::IsTrue(clause_grouper->GetClauseGroupWoSyn()->GetClauses().size() == 3);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWoSelectSyn().size() == 2);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWithSelectSyn().size() == 0);
        }

        TEST_METHOD(NoSynClausesAndClausesWoSelectSyn3) {
            string query_string = "variable v,v1,v2,v3; stmt s1, s2, s3, s4; Select v such that Follows(1, 5) and Parent*(1, 5) with 2 = \"test\" such that Modifies(s2, v1) and Uses (s2, v2) such that Uses(s3, v2)";

            shared_ptr<Query> query = query_builder_->GetQuery(query_string);

            shared_ptr<ClauseGrouper> clause_grouper = make_shared<OptimizedClauseGrouper>(*(query->GetAllClauses()), query->GetSelectSynonyms());

            Assert::IsTrue(clause_grouper->GetClauseGroupWoSyn()->GetClauses().size() == 3);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWoSelectSyn().size() == 1);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWithSelectSyn().size() == 0);
        }

        TEST_METHOD(ClausesWithAndWoSelectSyn) {
            string query_string = "variable v,v1,v2,v3; stmt s1, s2, s3, s4; Select v such that Follows(s3, 5) and Parent*(1, s2) with v.varName = s2.stmt# such that Modifies(s2, v1) and Uses (s2, v2) such that Uses(s3, v2)";

            shared_ptr<Query> query = query_builder_->GetQuery(query_string);

            shared_ptr<ClauseGrouper> clause_grouper = make_shared<OptimizedClauseGrouper>(*(query->GetAllClauses()), query->GetSelectSynonyms());

            Assert::IsTrue(clause_grouper->GetClauseGroupWoSyn()->GetClauses().size() == 0);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWoSelectSyn().size() == 0);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWithSelectSyn().size() == 1);
        }

        TEST_METHOD(ClausesWithAndWoSelectSyn1) {
            string query_string = "variable v,v1,v2,v3; stmt s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;"
                "Select v such that Follows(s1, 5) and Parent * (1, s2) with v.varName = s1.stmt# such that Modifies(s2, v1) and Uses(s2, v2) such that Uses(s3, v2)";

            shared_ptr<Query> query = query_builder_->GetQuery(query_string);

            shared_ptr<ClauseGrouper> clause_grouper = make_shared<OptimizedClauseGrouper>(*(query->GetAllClauses()), query->GetSelectSynonyms());

            Assert::IsTrue(clause_grouper->GetClauseGroupWoSyn()->GetClauses().size() == 0);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWoSelectSyn().size() == 1);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWithSelectSyn().size() == 1);
        }

        TEST_METHOD(ClausesWithSelectSyn) {
            string query_string = "variable v,v1,v2,v3; stmt s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;"
                "Select s3 such that Next(s1, s2) and Next(s2, s3) and Next(s3, s4) and Next(s4, s5) and Next*(s5, s6) and Affects(s6, s7)";

            shared_ptr<Query> query = query_builder_->GetQuery(query_string);

            shared_ptr<ClauseGrouper> clause_grouper = make_shared<OptimizedClauseGrouper>(*(query->GetAllClauses()), query->GetSelectSynonyms());

            Assert::IsTrue(clause_grouper->GetClauseGroupWoSyn()->GetClauses().size() == 0);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWoSelectSyn().size() == 0);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWithSelectSyn().size() == 1);
        }

        TEST_METHOD(ClausesWithSelectSyn_SelectSynNotInClause) {
            string query_string = "variable v,v1,v2,v3; stmt s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;"
                "Select <s3, s9> such that Next(s1, s2) and Next(s2, s3) and Next(s3, s4) and Next(s4, s5) and Next*(s5, s6) and Affects(s6, s7)";

            shared_ptr<Query> query = query_builder_->GetQuery(query_string);

            shared_ptr<ClauseGrouper> clause_grouper = make_shared<OptimizedClauseGrouper>(*(query->GetAllClauses()), query->GetSelectSynonyms());

            Assert::IsTrue(clause_grouper->GetClauseGroupWoSyn()->GetClauses().size() == 0);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWoSelectSyn().size() == 0);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWithSelectSyn().size() == 1);
        }


        TEST_METHOD(ClausesWithAndWoSelectSyn_MultipleGroups) {
            string query_string = "variable v,v1,v2,v3; stmt s1, s2, s3, s4, s5, s6, s7, s8, s9, s10;"
                "Select <v, s2> such that Follows(s1, 5) and Parent *(1, s2) with v.varName = s1.stmt# such that Modifies(s3, v2) and Uses(s3, v2) such that Uses(s4, v3)";

            shared_ptr<Query> query = query_builder_->GetQuery(query_string);

            shared_ptr<ClauseGrouper> clause_grouper = make_shared<OptimizedClauseGrouper>(*(query->GetAllClauses()), query->GetSelectSynonyms());

            Assert::IsTrue(clause_grouper->GetClauseGroupWoSyn()->GetClauses().size() == 0);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWoSelectSyn().size() == 2);
            Assert::IsTrue(clause_grouper->GetClauseGroupsWithSelectSyn().size() == 2);
        }
    };

}
