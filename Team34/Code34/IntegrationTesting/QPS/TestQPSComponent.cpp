#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../SPA/QPS/parser/QueryBuilder.h"
#include "../../SPA/QPS/stub/RelationStubFactory.h"
#include "../../SPA/QPS/stub/ReadPKBManagerStub.h"
#include "../../SPA/QPS/DataRetriever.h"
#include "../../SPA/QPS/QueryEvaluator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::shared_ptr;
using std::pair;
using std::string;

namespace IntegrationTesting
{
	TEST_CLASS(TestQPSComponent)
	{
	private:
		shared_ptr<QueryBuilder> query_builder_ = shared_ptr<QueryBuilder>(new QueryBuilder());
		std::shared_ptr<ReadPKBManager> pkb_stub = std::make_shared<ReadPKBManagerStub>();
		shared_ptr<DataRetriever> data_retriever_ = shared_ptr<DataRetriever>(new DataRetriever(pkb_stub));
	public:
		TEST_METHOD(BasicQPSComponentTest)
		{
			string query_string = "variable v; Select v";


			bool isValid = true;
			shared_ptr<Query> query;

			try {
				query = query_builder_->GetQuery(query_string);
			}
			catch (...) {
				isValid = false;
			}

			Assert::IsTrue(isValid);

			QueryEvaluator evaluator(*query, *data_retriever_);
			evaluator.Evaluate();
			vector<std::string> res = evaluator.ExtractResult();
			Assert::IsTrue(res.size() == 3);


			vector<string> correct_res = { "x","y","z" };

			for (string key: correct_res) {
				if (!std::count(res.begin(), res.end(), key)) {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
		}
	};

}