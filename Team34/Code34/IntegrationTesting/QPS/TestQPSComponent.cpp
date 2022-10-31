#include "stdafx.h"
#include "CppUnitTest.h"

#include "../../SPA/QPS/parser/QueryBuilder.h"
#include "../../UnitTesting/stub/RelationStubFactory.h"
#include "../../UnitTesting/stub/ReadPKBManagerStub.h"
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
		TEST_METHOD(VariableQPSComponentTest)
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

		TEST_METHOD(BooleanTrueQPSComponentTest)
		{
			string query_string = "stmt s1; Select BOOLEAN such that Follows(_,s1)";


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
			Assert::IsTrue(res.size() == 1);


			vector<string> correct_res = { "TRUE" };

			for (string key : correct_res) {
				if (!std::count(res.begin(), res.end(), key)) {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
		}

		TEST_METHOD(BooleanFalseQPSComponentTest)
		{
			string query_string = "stmt s1; Select BOOLEAN such that Follows(6,s1)";


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
			Assert::IsTrue(res.size() == 1);


			vector<string> correct_res = { "FALSE" };

			for (string key : correct_res) {
				if (!std::count(res.begin(), res.end(), key)) {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
		}

		TEST_METHOD(BooleanTrueQPSComponentWith1)
		{
			string query_string = "Select BOOLEAN with 12 = 12";


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
			Assert::IsTrue(res.size() == 1);

			vector<string> correct_res = { "TRUE" };

			for (string key : correct_res) {
				if (!std::count(res.begin(), res.end(), key)) {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
		}

		TEST_METHOD(BooleanTrueQPSComponentWith2)
		{
			string query_string = "procedure p,p2;\n Select BOOLEAN with p.procName  = \"Foo1\" and p2.procName = \"Nine\"";


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
			Assert::IsTrue(res.size() == 1);

			vector<string> correct_res = { "TRUE" };

			for (string key : correct_res) {
				if (!std::count(res.begin(), res.end(), key)) {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
		}

		TEST_METHOD(BooleanTrueQPSComponentCalls)
		{
			string query_string = "Select BOOLEAN such that Calls (_,_)";


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
			Assert::IsTrue(res.size() == 1);

			vector<string> correct_res = { "TRUE" };

			for (string key : correct_res) {
				if (!std::count(res.begin(), res.end(), key)) {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
		}

		TEST_METHOD(MultipleReturnQPSComponentModifies)
		{
			string query_string = "procedure p, q; assign a; Select <p, q> such that Modifies(\"func1\", \"x\")";


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
			Assert::IsTrue(res.size() == 9);

			vector<string> correct_res = { "Foo1 Foo1", "Foo1 bar", "Foo1 Nine", "bar bar", "bar Foo1", "bar Nine" ,"Nine Nine", "Nine bar", "Nine Foo1"};

			for (string key : correct_res) {
				if (!std::count(res.begin(), res.end(), key)) {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
		}

		TEST_METHOD(MultipleReturnQPSComponentSuchThatCalls)
		{
			//string query_string = "assign a; while w; Select <a.stmt#, w> such that Calls*(\"Foo1\", \"Nine\") and Modifies(\"func1\", \"x\")";
			string query_string = "assign a; while w; Select <a, w> such that Calls*(\"Foo1\", \"Nine\") and Modifies(\"func1\", \"x\")";

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

			Assert::IsTrue(res.size() == 4);

			vector<string> correct_res = { "2 1", "4 1", "5 1", "6 1" };
			for (string key : correct_res) {
				if (!std::count(res.begin(), res.end(), key)) {
					isValid = false;
				}
			}

			Assert::IsTrue(isValid);
		}
	};

}