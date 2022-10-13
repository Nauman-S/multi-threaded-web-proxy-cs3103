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
			calls_manager_.SetCalls("two", "three");
			Assert::AreEqual(2, int(calls_manager_.GetAllCallsRelations()->size()));
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

			std::shared_ptr<std::unordered_set<Procedure>> callee_one = calls_manager_.GetCalleeFromCaller("one");
			Assert::IsTrue(callee_one->find("two") != callee_one->end());

			std::shared_ptr<std::unordered_set<Procedure>> callee_two = calls_manager_.GetCalleeFromCaller("two");
			Assert::IsTrue(callee_two->find("three") != callee_two->end());

			std::shared_ptr<std::unordered_set<Procedure>> callee_three = calls_manager_.GetCalleeFromCaller("three");
			Assert::AreEqual(0, int(callee_three->size()));

			calls_manager_.SetCalls("one", "four");
			callee_one = calls_manager_.GetCalleeFromCaller("one");
			Assert::IsTrue(callee_one->find("two") != callee_one->end());
			Assert::IsTrue(callee_one->find("four") != callee_one->end());
		}

		TEST_METHOD(TestGetCallerFromCallee)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");

			std::shared_ptr<std::unordered_set<Procedure>> caller_one = calls_manager_.GetCallerFromCallee("one");
			Assert::AreEqual(0, int(caller_one->size()));

			std::shared_ptr<std::unordered_set<Procedure>> caller_two = calls_manager_.GetCallerFromCallee("two");
			Assert::IsTrue(caller_two->find("one") != caller_two->end());

			std::shared_ptr<std::unordered_set<Procedure>> caller_three = calls_manager_.GetCallerFromCallee("three");
			Assert::IsTrue(caller_three->find("two") != caller_three->end());

			calls_manager_.SetCalls("four", "three");
			caller_three = calls_manager_.GetCallerFromCallee("three");
			Assert::IsTrue(caller_three->find("two") != caller_three->end());
			Assert::IsTrue(caller_three->find("four") != caller_three->end());
		}

		TEST_METHOD(TestGetAllCallers)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			std::shared_ptr<std::unordered_set<Procedure>> all_callers = calls_manager_.GetAllCallers();
			Assert::AreEqual(2, int(all_callers->size()));
			Assert::IsTrue(all_callers->find("one") != all_callers->end());
			Assert::IsTrue(all_callers->find("two") != all_callers->end());

			calls_manager_.SetCalls("one", "four");
			all_callers = calls_manager_.GetAllCallers();
			Assert::AreEqual(2, int(all_callers->size()));
		}

		TEST_METHOD(TestGetAllCallees)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");
			std::shared_ptr<std::unordered_set<Procedure>> all_callees = calls_manager_.GetAllCallees();
			Assert::AreEqual(2, int(all_callees->size()));
			Assert::IsTrue(all_callees->find("two") != all_callees->end());
			Assert::IsTrue(all_callees->find("three") != all_callees->end());

			calls_manager_.SetCalls("four", "two");
			all_callees = calls_manager_.GetAllCallees();
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

			std::shared_ptr<std::unordered_set<Procedure>> callee_one = calls_manager_.GetAllCalleeFromCaller("one");
			Assert::IsTrue(callee_one->find("two") != callee_one->end());
			Assert::IsTrue(callee_one->find("three") != callee_one->end());

			std::shared_ptr<std::unordered_set<Procedure>> callee_two = calls_manager_.GetAllCalleeFromCaller("two");
			Assert::IsTrue(callee_two->find("three") != callee_two->end());

			std::shared_ptr<std::unordered_set<Procedure>> callee_three = calls_manager_.GetAllCalleeFromCaller("three");
			Assert::AreEqual(0, int(callee_three->size()));

			calls_manager_.SetCalls("one", "four");
			callee_one = calls_manager_.GetAllCalleeFromCaller("one");
			Assert::AreEqual(3, int(callee_one->size()));Assert::IsTrue(callee_one->find("two") != callee_one->end());
			Assert::IsTrue(callee_one->find("three") != callee_one->end());
			Assert::IsTrue(callee_one->find("two") != callee_one->end());
			Assert::IsTrue(callee_one->find("three") != callee_one->end());
			Assert::IsTrue(callee_one->find("four") != callee_one->end());
		}

		TEST_METHOD(TestGetAllCallersFromCallee)
		{
			calls_manager_.SetCalls("one", "two");
			calls_manager_.SetCalls("two", "three");

			std::shared_ptr<std::unordered_set<Procedure>> caller_one = calls_manager_.GetAllCallerFromCallee("one");
			Assert::AreEqual(0, int(caller_one->size()));

			std::shared_ptr<std::unordered_set<Procedure>> caller_two = calls_manager_.GetAllCallerFromCallee("two");
			Assert::IsTrue(caller_two->find("one") != caller_two->end());

			std::shared_ptr<std::unordered_set<Procedure>> caller_three = calls_manager_.GetAllCallerFromCallee("three");
			Assert::IsTrue(caller_three->find("one") != caller_three->end());
			Assert::IsTrue(caller_three->find("two") != caller_three->end());

			calls_manager_.SetCalls("four", "two");
			caller_two = calls_manager_.GetAllCallerFromCallee("two");
			Assert::IsTrue(caller_two->find("one") != caller_two->end());
			Assert::IsTrue(caller_two->find("four") != caller_two->end());
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