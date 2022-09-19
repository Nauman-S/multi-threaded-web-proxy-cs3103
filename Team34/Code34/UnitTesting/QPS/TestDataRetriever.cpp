#include "stdafx.h"
#include "CppUnitTest.h"

#include <memory>
#include <unordered_set>
#include <vector>

#include "../../SPA/PKB/ReadPKBManager.h"
#include "../../SPA/QPS/stub/RelationStubFactory.h"
#include "../../SPA/QPS/stub/ReadPKBManagerStub.h"
#include "../../SPA/QPS/DataRetriever.h"
#include "../../SPA/QPS/relation/Rel.h"
#include "../../SPA/QPS/relation/ModifiesPRel.h"
#include "../../SPA/QPS/relation/ModifiesSRel.h"
#include "../../SPA/QPS/relation/UsesPRel.h"
#include "../../SPA/QPS/relation/UsesSRel.h"
#include "../../SPA/QPS/relation/FollowsRel.h"
#include "../../SPA/QPS/relation/FollowsTRel.h"
#include "../../SPA/QPS/relation/ParentRel.h"
#include "../../SPA/QPS/relation/ParentTRel.h"
#include "../../SPA/QPS/reference/ProcRef.h"
#include "../../SPA/QPS/reference/VarRef.h"
#include "../../SPA/QPS/reference/StmtRef.h"
#include "../../SPA/QPS/reference/AssignRef.h"
#include "../../SPA/QPS/reference/ValType.h"
#include "../../SPA/QPS/query_result/ResWrapper.h"
#include "../../SPA/QPS/../Utils/type/RefType.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using std::shared_ptr;
using std::unordered_set;
using std::pair;
using std::vector;
using std::string;

namespace UnitTesting
{
	TEST_CLASS(TestDataRetriever)
	{
	private:
		RelationStubFactory rel_stub_factory_;
		std::shared_ptr<ReadPKBManager> pkb_stub = std::make_shared<ReadPKBManagerStub>();
		shared_ptr<DataRetriever> data_retriever_ = shared_ptr<DataRetriever>(new DataRetriever(pkb_stub));

	public:
		TEST_METHOD(TestRetrieveModifiesP)
		{
			/*
				Expected results:
				func1 modifies x
			*/
			shared_ptr<Rel> rel_ptr;
			shared_ptr<ResWrapper> res;

			rel_ptr = rel_stub_factory_.GetModifiesP_proc_name_var_name();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetModifiesP_proc_name_var_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"x"}, *(res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"x"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetModifiesP_proc_syn_var_name();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"func1"}, *(res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"func1"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetModifiesP_proc_syn_var_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(vector<StrPair>{ {"func1", "x"}}, *(res->GetTable()->GetRows()));
			Assert::IsTrue(vector<StrPair>{ {"func1", "x"}} == *(res->GetTable()->GetRows()));

			rel_ptr = rel_stub_factory_.GetModifiesP_proc_name_var_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetModifiesP_proc_syn_var_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"func1"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"func1"} == *(res->GetSet()->GetDomain()));
			
		}

		TEST_METHOD(TestRetrieveModifiesS)
		{
			/*
				Expected results:
				stmt 5 modifies x
			*/
			shared_ptr<Rel> rel_ptr;
			shared_ptr<ResWrapper> res;

			rel_ptr = rel_stub_factory_.GetModifiesS_stmt_num_var_name();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetModifiesS_stmt_num_var_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"x"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"x"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetModifiesS_stmt_syn_var_name();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"5"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"5"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetModifiesS_stmt_syn_var_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(vector<StrPair>{ {"5", "x"}}, * (res->GetTable()->GetRows()));
			Assert::IsTrue(vector<StrPair>{ {"5", "x"}} == *(res->GetTable()->GetRows()));

			rel_ptr = rel_stub_factory_.GetModifiesS_stmt_num_var_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetModifiesS_stmt_syn_var_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"5"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"5"} == *(res->GetSet()->GetDomain()));
		}

		TEST_METHOD(TestRetrieveUsesP)
		{
			/*
				Expected results:
				func2 uses y
			*/
			shared_ptr<Rel> rel_ptr;
			shared_ptr<ResWrapper> res;

			rel_ptr = rel_stub_factory_.GetUsesP_proc_name_var_name();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetUsesP_proc_name_var_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"y"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"y"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetUsesP_proc_syn_var_name();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"func2"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"func2"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetUsesP_proc_syn_var_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(vector<StrPair>{ {"func2", "y"}}, * (res->GetTable()->GetRows()));
			Assert::IsTrue(vector<StrPair>{ {"func2", "y"}} == *(res->GetTable()->GetRows()));

			rel_ptr = rel_stub_factory_.GetUsesP_proc_name_var_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetUsesP_proc_syn_var_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"func2"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"func2"} == *(res->GetSet()->GetDomain()));
		}

		TEST_METHOD(TestRetrieveUsesS)
		{
			/*
				Expected results:
				stmt 5 uses y
			*/
			shared_ptr<Rel> rel_ptr;
			shared_ptr<ResWrapper> res;

			rel_ptr = rel_stub_factory_.GetUsesS_stmt_num_var_name();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetUsesS_stmt_num_var_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"y"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"y"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetUsesS_stmt_syn_var_name();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"5"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"5"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetUsesS_stmt_syn_var_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(vector<StrPair>{ {"5", "y"}}, * (res->GetTable()->GetRows()));
			Assert::IsTrue(vector<StrPair>{ {"5", "y"}} == *(res->GetTable()->GetRows()));

			rel_ptr = rel_stub_factory_.GetUsesS_stmt_num_var_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetUsesS_stmt_syn_var_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			// Assert::AreEqual(unordered_set<string>{"5"}, * (res->GetSet()->GetDomain()));
			Assert::IsTrue(unordered_set<string>{"5"} == *(res->GetSet()->GetDomain()));
		}

		TEST_METHOD(TestRetrieveFollows)
		{
			/*
				Expected results:
				stmt 3 follows stmt 2 (Follows(2,3))
			*/
			shared_ptr<Rel> rel_ptr;
			shared_ptr<ResWrapper> res;

			rel_ptr = rel_stub_factory_.GetFollows_stmt_num_stmt_num();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetFollows_stmt_num_stmt_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(unordered_set<string>{"3"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetFollows_stmt_syn_stmt_num();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(unordered_set<string>{"2"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetFollows_stmt_syn_stmt_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(vector<StrPair>{ {"2", "3"}} == *(res->GetTable()->GetRows()));

			rel_ptr = rel_stub_factory_.GetFollows_stmt_wildcard_stmt_num();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetFollows_stmt_num_stmt_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetFollows_stmt_syn_stmt_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(unordered_set<string>{"2"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetFollows_stmt_wildcard_stmt_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(unordered_set<string>{"3","6"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetFollows_stmt_wildcard_stmt_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());
		}

		TEST_METHOD(TestRetrieveFollowsT)
		{
			/*
				Expected results:
				FollowsT(2,6)
			*/
			shared_ptr<Rel> rel_ptr;
			shared_ptr<ResWrapper> res;

			rel_ptr = rel_stub_factory_.GetFollowsT_stmt_num_stmt_num();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetFollowsT_stmt_num_stmt_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(unordered_set<string>{"6"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetFollowsT_stmt_syn_stmt_num();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(unordered_set<string>{"2"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetFollowsT_stmt_syn_stmt_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(vector<StrPair>{ {"2", "6"}} == *(res->GetTable()->GetRows()));

			rel_ptr = rel_stub_factory_.GetFollowsT_stmt_wildcard_stmt_num();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetFollowsT_stmt_num_stmt_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());

			rel_ptr = rel_stub_factory_.GetFollowsT_stmt_syn_stmt_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(unordered_set<string>{"2"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetFollowsT_stmt_wildcard_stmt_syn();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(unordered_set<string>{"3","6"} == *(res->GetSet()->GetDomain()));

			rel_ptr = rel_stub_factory_.GetFollowsT_stmt_wildcard_stmt_wildcard();
			res = rel_ptr->GetMatch(*data_retriever_);
			Assert::IsTrue(res->IsValid());
		}

	};

}