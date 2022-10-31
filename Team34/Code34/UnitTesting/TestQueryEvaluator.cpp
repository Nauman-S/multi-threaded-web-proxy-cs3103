#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/QPS/parser/QueryBuilder.h"
#include "../SPA/Utils/error/SyntaxError.h"
#include "../SPA/Utils/error/SemanticError.h"
#include "../SPA/QPS/query_result/Table.h"

using std::vector;
using std::string;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
    TEST_CLASS(TestQueryEvaluator) {
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

}