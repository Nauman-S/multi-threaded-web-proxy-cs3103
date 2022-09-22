#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/PKB/manager/CallsManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestCallsManager)
	{
	private:
		CallsManager calls_manager_;
	public:
		TEST_METHOD(TestSetCalls)
		{
			calls_manager_.SetCalls("one", "two");
			Assert::AreEqual(1, int(calls_manager_.GetAllCallsRelations()->size()));
			calls_manager_.SetCalls("two", "three");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallsRelations()->size()));
		}

		TEST_METHOD(TestCheckCalls)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			Assert::IsTrue(calls_manager_.CheckCalls("one", "two"));
			Assert::IsTrue(calls_manager_.CheckCalls("two", "three"));
			Assert::IsFalse(calls_manager_.CheckCalls("one", "three"));
		}

		TEST_METHOD(TestIsEmpty)
		{
			Assert::IsTrue(calls_manager_.IsEmpty());
			calls_manager_.SetCalls("one", "two");
			Assert::IsFalse(calls_manager_.IsEmpty());
		}

		TEST_METHOD(TestGetCalleeFromCaller)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			Assert::AreEqual(1, int(calls_manager_.GetCalleeFromCaller("one")->size()));
			Assert::AreEqual(1, int(calls_manager_.GetCalleeFromCaller("two")->size()));
			Assert::AreEqual(0, int(calls_manager_.GetCalleeFromCaller("three")->size()));
			calls_manager_.SetCalls("one", "four");
			Assert::AreEqual(2, int(calls_manager_.GetCalleeFromCaller("one")->size()));
		}

		TEST_METHOD(TestGetCallerFromCallee)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			Assert::AreEqual(0, int(calls_manager_.GetCallerFromCallee("one")->size()));
			Assert::AreEqual(1, int(calls_manager_.GetCallerFromCallee("two")->size()));
			Assert::AreEqual(1, int(calls_manager_.GetCallerFromCallee("three")->size()));
			calls_manager_.SetCalls("four", "three");
			Assert::AreEqual(2, int(calls_manager_.GetCallerFromCallee("three")->size()));
		}

		TEST_METHOD(TestGetAllCallers)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallers()->size()));
			calls_manager_.SetCalls("one", "four");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallers()->size()));
		}

		TEST_METHOD(TestGetAllCallees)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallees()->size()));
			calls_manager_.SetCalls("four", "two");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallees()->size()));
		}

		TEST_METHOD(TestGetAllCallsRelations)
		{
			Assert::AreEqual(0, int(calls_manager_.GetAllCallsRelations()->size()));
			calls_manager_.SetCalls("one", "two");
			Assert::AreEqual(1, int(calls_manager_.GetAllCallsRelations()->size()));
			calls_manager_.SetCalls("two", "three");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallsRelations()->size()));
		}

		TEST_METHOD(TestSetCallsT)
		{
			calls_manager_.SetCallsT("one", "two");
			calls_manager_.SetCallsT("two", "three");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallsTRelations()->size()));
			calls_manager_.SetCallsT("two", "three");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallsTRelations()->size()));
		}

		TEST_METHOD(TestCheckCallsT)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			Assert::IsTrue(calls_manager_.CheckCallsT("one", "two"));
			Assert::IsTrue(calls_manager_.CheckCallsT("two", "three"));
			Assert::IsTrue(calls_manager_.CheckCallsT("one", "three"));
			Assert::IsFalse(calls_manager_.CheckCallsT("two", "one"));
			Assert::IsFalse(calls_manager_.CheckCallsT("three", "one"));
		}

		TEST_METHOD(TestGetAllCalleeFromCaller)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			Assert::AreEqual(2, int(calls_manager_.GetAllCalleeFromCaller("one")->size()));
			Assert::AreEqual(1, int(calls_manager_.GetAllCalleeFromCaller("two")->size()));
			Assert::AreEqual(0, int(calls_manager_.GetAllCalleeFromCaller("three")->size()));
			calls_manager_.SetCalls("one", "four");
			Assert::AreEqual(3, int(calls_manager_.GetAllCalleeFromCaller("one")->size()));
		}

		TEST_METHOD(TestGetAllCallersFromCallee)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			Assert::AreEqual(0, int(calls_manager_.GetAllCallerFromCallee("one")->size()));
			Assert::AreEqual(1, int(calls_manager_.GetAllCallerFromCallee("two")->size()));
			Assert::AreEqual(2, int(calls_manager_.GetAllCallerFromCallee("three")->size()));
			calls_manager_.SetCalls("four", "two");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallerFromCallee("two")->size()));
		}

		TEST_METHOD(TestGetAllCallsTRelations)
		{
			Assert::AreEqual(0, int(calls_manager_.GetAllCallsTRelations()->size()));
			calls_manager_.SetCallsT("one", "two");
			calls_manager_.SetCallsT("two", "three");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallsTRelations()->size()));
			calls_manager_.SetCallsT("one", "three");
			Assert::AreEqual(3, int(calls_manager_.GetAllCallsTRelations()->size()));
		}
	};
}