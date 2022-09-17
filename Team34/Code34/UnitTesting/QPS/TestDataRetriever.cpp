#include "../stdafx.h"
#include "CppUnitTest.h"

#include <memory>

#include "../../SPA/PKB/manager/FollowsManager.h"
#include "../../SPA/QPS/stub/RelationStubFactory.h"
#include "../../SPA/QPS/stub/ReadPKBManagerStub.h"
#include "../../SPA/PKB/ReadPKBManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestDataRetriever)
	{
	private:
		RelationStubFactory rel_stub_factory_;
		// std::unique_ptr<ReadPKBManager> pkb_stub = std::make_unique<ReadPKBManagerStub>();
		// DataRetriever data_retriever(pkb_stub);
		DataRetriever data_retriever_(std::make_unique<ReadPKBManager>());

	public:
		TEST_METHOD(TestRetrieveModifiesP)
		{
			auto rel_ptr = rel_stub_factory_.GetModifiesP_proc_name_var_name();
			data_retriever.retrieve()
		}

		TEST_METHOD(TestRetrieveModifiesS)
		{

		}

		TEST_METHOD(TestRetrieveUsesP)
		{

		}

		TEST_METHOD(TestRetrieveUsesS)
		{

		}

	};

}