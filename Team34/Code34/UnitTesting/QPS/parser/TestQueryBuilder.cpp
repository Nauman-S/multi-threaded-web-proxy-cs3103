#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/QPS/parser/QueryBuilder.h"
#include "../SPA/QPS/query_result/ResType.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryBuilder)
	{
	private:
		shared_ptr<QueryBuilder> query_builder_ = shared_ptr<QueryBuilder>(new QueryBuilder());
	public:

		TEST_METHOD(TestValidSelectAllVariableQuery)
		{
			const std::string query_ = "variable V; Select V";
			const std::string var = "V";
			shared_ptr<Query> query = query_builder_->GetQuery(query_);

			//Check if entity references are correct
			Assert::IsTrue(query->GetSelectTuple()->size() == 1);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kVarRef);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() ==  ValType::kSynonym);
			Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), var);

			//Check if such that clauses are correct
			Assert::IsTrue(query->GetRelations()->size() == 0);

			//Check if all pattern clauses are correct
			Assert::IsTrue(query->GetPatterns()->size() == 0);
		}

		TEST_METHOD(TestValidBasicSuchThat) {

			const std::string query_ = "variable V; Select V such that Uses(3,V)";
			const std::string var_ = "V";
			std::string lhs_value_ = "3";
			std::string rhs_value_ = var_;

			shared_ptr<Query> query = query_builder_->GetQuery(query_);

			//Check if entity references are correct
			Assert::IsTrue(query->GetSelectTuple()->size() == 1);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kVarRef);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
			Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), var_);

			//Check if such that clauses are correct
			Assert::IsTrue(query->GetRelations()->size() == 1);
			Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == RelType::kUsesSRel);
			Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
			Assert::AreEqual(query->GetRelations()->at(0)->LhsValue() , lhs_value_);
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kConst);
			Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kVarRef);
			Assert::AreEqual(query->GetRelations()->at(0)->RhsValue(), rhs_value_);
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kSynonym);

			//Check if all pattern clauses are correct
			Assert::IsTrue(query->GetPatterns()->size() == 0);
		};

	};
}