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
			const std::string valid_select_all_query_ = "variable V; Select V";
			const std::string var = "V";

			shared_ptr<Query> query = query_builder_->GetQuery(valid_select_all_query_);

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

	};
}