#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/QPS/parser/QueryBuilder.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestQueryBuilder)
	{
	private:
		shared_ptr<QueryBuilder> query_builder_ = shared_ptr<QueryBuilder>(new QueryBuilder());
	public:

		TEST_METHOD(TestSelectAllVariableQuery)
		{
			const std::string valid_select_all_query_ = "variable v; Select v";
			shared_ptr<Query> query = query_builder_->GetQuery(valid_select_all_query_);
			Assert::AreEqual((int)query->GetSelectTuple()->size(), 1);
		}

	};
}