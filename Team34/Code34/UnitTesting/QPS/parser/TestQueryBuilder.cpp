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
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
			Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), var);

			//Check if such that clauses are correct
			Assert::IsTrue(query->GetRelations()->size() == 0);

			//Check if all pattern clauses are correct
			Assert::IsTrue(query->GetPatterns()->size() == 0);
		};

		TEST_METHOD(TestValidBasicLineNumberSuchThatUses) {

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
			Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kLineNum);
			Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kVarRef);
			Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kSynonym);

			//Check if all pattern clauses are correct
			Assert::IsTrue(query->GetPatterns()->size() == 0);
		};

		TEST_METHOD(TestValidBasicVariableProcedureNameSuchThatUses) {

			const std::string query_ = "variable VAR12; Select VAR12 such that Uses(\"MAIN\", VAR12)";
			const std::string var_ = "VAR12";
			std::string lhs_value_ = "MAIN";
			std::string rhs_value_ = var_;

			shared_ptr<Query> query = query_builder_->GetQuery(query_);

			//Check if entity references are correct
			Assert::IsTrue(query->GetSelectTuple()->size() == 1);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kVarRef);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
			Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), var_);

			//Check if such that clauses are correct
			Assert::IsTrue(query->GetRelations()->size() == 1);
			Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == RelType::kUsesPRel);
			Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kProcRef);
			Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kProcName);
			Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kVarRef);
			Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kSynonym);

			//Check if all pattern clauses are correct
			Assert::IsTrue(query->GetPatterns()->size() == 0);
		};

		TEST_METHOD(TestValidBasicProcedureSynonymSuchThatModifies) {

			const std::string query_ = "procedure P; Select P such that Modifies(P,\"X\")";
			const std::string proc_ = "P";
			std::string lhs_value_ = proc_;
			std::string rhs_value_ = "X";

			shared_ptr<Query> query = query_builder_->GetQuery(query_);

			//Check if entity references are correct
			Assert::IsTrue(query->GetSelectTuple()->size() == 1);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kProcRef);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
			Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), proc_);

			////Check if such that clauses are correct
			Assert::IsTrue(query->GetRelations()->size() == 1);
			Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == RelType::kModifiesPRel);
			Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kProcRef);
			Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kSynonym);
			Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kVarRef);
			Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kVarName);

			//Check if all pattern clauses are correct
			Assert::IsTrue(query->GetPatterns()->size() == 0);
		};

		TEST_METHOD(TestValidBasicWhileSynonymSuchThatModifiesWildCard) {

			const std::string query_ = "while W; Select W such that Modifies(W,_)";
			const std::string while_ = "W";
			std::string lhs_value_ = while_;
			std::string rhs_value_ = "";

			shared_ptr<Query> query = query_builder_->GetQuery(query_);

			//Check if entity references are correct
			Assert::IsTrue(query->GetSelectTuple()->size() == 1);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kWhileRef);
			Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
			Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), while_);

			////Check if such that clauses are correct
			Assert::IsTrue(query->GetRelations()->size() == 1);
			Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == RelType::kModifiesSRel);
			Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kWhileRef);
			Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kSynonym);
			Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kVarRef);
			Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
			Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kWildcard);

			//Check if all pattern clauses are correct
			Assert::IsTrue(query->GetPatterns()->size() == 0);
		};

	};
}