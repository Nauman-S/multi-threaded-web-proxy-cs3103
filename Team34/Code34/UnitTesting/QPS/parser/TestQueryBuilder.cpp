#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/QPS/parser/QueryBuilder.h"
#include "../SPA/Utils/error/SyntaxError.h"
#include "../SPA/Utils/error/SemanticError.h"
#include "../SPA/QPS/query_result/ResType.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting {
    TEST_CLASS(TestQueryBuilder) {
private:
    shared_ptr<QueryBuilder> query_builder_ = shared_ptr<QueryBuilder>(new QueryBuilder());
public:
    TEST_METHOD(TestValidSelectAllVariableQuery) {
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

    TEST_METHOD(Valid_MultipleDeclaration) {
        const std::string query_ = "variable V, v1  ,  v2; Select V";
        const std::string var = "V";
        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Assert::IsTrue(query->);

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

    TEST_METHOD(Valid_MultipleDeclaration_MultipleSelect) {
        const std::string query_ = "variable v, v1  ,  v2; Select <v, v1,  v2>";
        const std::string var = "v";
        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Assert::IsTrue(query->);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 3);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kVarRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), var);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_MultipleDeclaration_SelectBoolean) {
        const std::string query_ = "variable v, v1  ,  v2; Select BOOLEAN";
        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->IsBoolean());

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
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kUsesSRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kLineNum);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kVarRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kSynonym);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(SyntaxError_UncapitalizedSelect) {
        const std::string query_ = "assign a; variable haha; select haha)";
        bool syntax_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SyntaxError&) {
            syntax_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntax_error_thrown);
    };

    TEST_METHOD(SyntaxError_ExtraSemicolonInTheEnd) {
        const std::string query_ = "Assign a; variable haha; Select haha such that Parent* (_,_) pattern a(\"v\", \" (x + y) * z + p \");";
        bool syntax_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SyntaxError&) {
            syntax_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntax_error_thrown);
    };

    TEST_METHOD(SyntaxError_CapitalizedDeclaration) {
        const std::string query_ = "Assign a; variable haha; Select haha such that Parent* (_,_) pattern a(\"v\", \" (x + y) * z + p \")";
        bool syntax_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SyntaxError&) {
            syntax_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntax_error_thrown);
    };
    TEST_METHOD(Valid_BasicVariable_ProcedureName_SuchThatUses) {

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
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kUsesPRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kProcRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kProcName);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kVarRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kSynonym);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicProcedureSynonym_SuchThatModifies) {

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
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kModifiesPRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kProcRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kSynonym);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kVarRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kVarName);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicWhileSynonym_SuchThatModifiesWildCard) {

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
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kModifiesSRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kWhileRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kSynonym);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kVarRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kWildcard);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicPrintSynonym_SuchThatFollows) {

        const std::string query_ = "print p;\n\n\n    Select       \n  p such that Follows     (23,45)";
        const std::string print_ = "p";
        std::string lhs_value_ = "23";
        std::string rhs_value_ = "45";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kPrintRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), print_);

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kFollowsRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kLineNum);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kLineNum);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicCall_SynonymSuchThatFollowsT) {

        const std::string query_ = "call c, c1; Select c1 such that Follows* (c, 13)";
        const std::string call_ = "c1";
        std::string lhs_value_ = "c";
        std::string rhs_value_ = "13";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kCallRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), call_);

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kFollowsTRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kCallRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kSynonym);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kLineNum);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicReadSynonym_SuchThatFollowsTWildCard) {
        const std::string query_ = "read Read57; Select Read57 such that Follows* ( _,   Read57)  ";
        const std::string read_ = "Read57";
        std::string lhs_value_ = "";
        std::string rhs_value_ = read_;

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kReadRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), read_);

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kFollowsTRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kWildcard);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kReadRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kSynonym);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };


    TEST_METHOD(Valid_BasicWhileSynonym_SuchThatParentWildCard) {

        const std::string query_ = "while w; Select w such that Parent (w,_)  ";
        const std::string while_ = "w";
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
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kParentRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kWhileRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kSynonym);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kWildcard);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicVariableSynonym_SuchThatParentTWildCard) {
        const std::string query_ = "variable v; Select v such that Parent* (_,_)  ";
        const std::string variable_ = "v";
        std::string lhs_value_ = "";
        std::string rhs_value_ = "";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kVarRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), variable_);

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kParentTRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kWildcard);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kWildcard);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicNextRel) {
        const std::string query_ = "stmt s1, s2; Select s1 such that Next (s1,s2)  ";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kNextRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicNextTRel) {
        const std::string query_ = "stmt s1; stmt s2; Select s1 such that Next*(s1,s2)  ";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kNextTRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };


    TEST_METHOD(Valid_BasicAffectsRel) {
        const std::string query_ = "stmt s1, s2; Select s1 such that Affects(s1,s2)  ";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kAffectsRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicAffectsTRel) {
        const std::string query_ = "stmt s1, s2; Select s1 such that Affects*(s1,s2)  ";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kAffectsTRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicCallsRel) {
        const std::string query_ = "procedure p1, p2; Select p1 such that Calls(p1, p2)  ";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kCallsRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kProcRef);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kProcRef);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };

    TEST_METHOD(Valid_BasicCallsTRel) {
        const std::string query_ = "procedure p1, p2; Select p1 such that Calls*(p1, p2)  ";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kCallsTRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kProcRef);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kProcRef);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
    };
    TEST_METHOD(SyntaxError_WrongRelationshipName) {
        const std::string query_ = "assign a; variable haha; select a such that ParentT (_,_) pattern a(\"v\", \" (x + y) * z + p \")";
        bool syntax_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SyntaxError&) {
            syntax_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntax_error_thrown);
    };
    TEST_METHOD(Valid_PatternClause_SelectedAssign_Identity_WildcardExpression) {

        const std::string query_ = "assign a; Select a pattern a(\"v\", _)  ";
        const std::string select_variable = "a";
        std::string lhs_value_ = "v";
        std::string rhs_value_ = "";
        std::string expr_str = "";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kAssignRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), select_variable);

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->VarValType() == ValType::kVarName);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtSyn() == select_variable);
        Assert::AreEqual(expr_str, query->GetPatterns()->at(0)->GetExprSpec()->GetInfix());

    };

    TEST_METHOD(Valid_PatternClause_SelectedAssign_Identity_PartialExpression) {

        const std::string query_ = "assign a; Select a pattern a(\"v\", _ \" x + 3 \"_)  ";
        const std::string select_variable = "a";
        std::string lhs_value_ = "v";
        std::string rhs_value_ = "";
        std::string expr_str = "x + 3";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kAssignRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), select_variable);

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->VarValType() == ValType::kVarName);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtSyn() == select_variable);
        Assert::AreEqual(expr_str, query->GetPatterns()->at(0)->GetExprSpec()->GetInfix());
    };

    TEST_METHOD(Valid_PatternClause_SelectedAssign_Identity_ExactExpression) {
        const std::string query_ = "assign a; Select a pattern a(\"v\", \" x + 3 \")";
        const std::string select_variable = "a";
        std::string lhs_value_ = "v";
        std::string rhs_value_ = "";
        std::string expr_str = "x + 3";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kAssignRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query->GetSelectTuple()->at(0)->GetName(), select_variable);

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->VarValType() == ValType::kVarName);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtSyn() == select_variable);
        Assert::AreEqual(expr_str, query->GetPatterns()->at(0)->GetExprSpec()->GetInfix());
    };

    TEST_METHOD(Valid_PatternClause_SelectedAssign_Identity_ExactExpressionWithBracket) {
        const std::string query_ = "assign a; Select a pattern a(\"v\", \" (x + y) * z + p \")";
        const std::string select_variable = "a";
        std::string lhs_value_ = "v";
        std::string rhs_value_ = "";
        std::string expr_str = "( x + y ) * z + p";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kAssignRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(select_variable, query->GetSelectTuple()->at(0)->GetName());

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->VarValType() == ValType::kVarName);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::AreEqual(select_variable, query->GetPatterns()->at(0)->StmtSyn());
        Assert::AreEqual(expr_str, query->GetPatterns()->at(0)->GetExprSpec()->GetInfix());
    };

    TEST_METHOD(Valid_PatternClause_SelectedAssign_Identity_ExactExpressionWithMultipleBracket) {
        const std::string query_ = "assign a; Select a pattern a(\"v\", \" ((1 + 2) * (3 + 4)) \")";
        const std::string select_variable = "a";
        std::string lhs_value_ = "v";
        std::string rhs_value_ = "";
        std::string expr_str = "( ( 1 + 2 ) * ( 3 + 4 ) )";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kAssignRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(select_variable, query->GetSelectTuple()->at(0)->GetName());

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->VarValType() == ValType::kVarName);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::AreEqual(select_variable, query->GetPatterns()->at(0)->StmtSyn());
        Assert::AreEqual(expr_str, query->GetPatterns()->at(0)->GetExprSpec()->GetInfix());
    };

    TEST_METHOD(Valid_PatternClause_SelectedAssign_Identity_ExactExpressionWithBracket_DifferentSelectAndAssignRef) {
        const std::string query_ = "assign a; variable v; Select v pattern a(\"v\", \" (x + y) * z + p \")";
        const std::string select_variable = "v";
        const std::string assign_variable = "a";
        std::string lhs_value_ = "v";
        std::string rhs_value_ = "";
        std::string expr_str = "( x + y ) * z + p";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kVarRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(select_variable, query->GetSelectTuple()->at(0)->GetName());

        ////Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->VarValType() == ValType::kVarName);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::AreEqual(assign_variable, query->GetPatterns()->at(0)->StmtSyn());
        Assert::AreEqual(expr_str, query->GetPatterns()->at(0)->GetExprSpec()->GetInfix());
    };

    TEST_METHOD(SyntaxError_PatternClause_RedundantClosingBrace) {
        const std::string query_ = "assign a; variable haha; Select a such that Parent* (_, _) pattern a(\"v\", \" (x + y)) * z + p \")    ";
        bool syntax_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SyntaxError&) {
            syntax_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntax_error_thrown);
    };

    TEST_METHOD(SyntaxError_PatternClause_RedundantOpeningBrace) {
        const std::string query_ = "assign a; variable haha; Select a such that Parent* (_, _) pattern a(\"v\", \" ((x + y) * z + p \")    ";
        bool syntax_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SyntaxError&) {
            syntax_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntax_error_thrown);
    };

    TEST_METHOD(Valid_PatternClause_And_SelectThatClause) {
        const std::string query_ = "assign a; variable haha; Select haha such that Parent* (_,_) pattern a(\"v\", \" (x + y) * z + p \")        ";
        const std::string select_variable = "haha";
        const std::string assign_variable = "a";
        std::string lhs_value_ = "";
        std::string rhs_value_ = "";
        std::string expr_str = "( x + y ) * z + p";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kVarRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(select_variable, query->GetSelectTuple()->at(0)->GetName());

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kParentTRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kWildcard);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kWildcard);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->VarValType() == ValType::kVarName);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::AreEqual(assign_variable, query->GetPatterns()->at(0)->StmtSyn());
        Assert::AreEqual(expr_str, query->GetPatterns()->at(0)->GetExprSpec()->GetInfix());
    };

    TEST_METHOD(Valid_SelectThatClause_And_PatternClause) {
        const std::string query_ = "assign a; variable haha; Select haha such that Parent* (_,_) pattern a(\"v\", \" (x + y) * z + p \")        ";
        const std::string select_variable = "haha";
        const std::string assign_variable = "a";
        std::string lhs_value_ = "";
        std::string rhs_value_ = "";
        std::string expr_str = "( x + y ) * z + p";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetRefType() == RefType::kVarRef);
        Assert::IsTrue(query->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(select_variable, query->GetSelectTuple()->at(0)->GetName());

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 1);
        Assert::IsTrue(query->GetRelations()->at(0)->GetRelType() == ClauseType::kParentTRel);
        Assert::IsTrue(query->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(lhs_value_, query->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().first == ValType::kWildcard);
        Assert::IsTrue(query->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(rhs_value_, query->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query->GetRelations()->at(0)->ValTypes().second == ValType::kWildcard);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->VarValType() == ValType::kVarName);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::AreEqual(assign_variable, query->GetPatterns()->at(0)->StmtSyn());
        Assert::AreEqual(expr_str, query->GetPatterns()->at(0)->GetExprSpec()->GetInfix());
    };




    TEST_METHOD(SyntaxError_IncompleteQueryWithoutSelectIdentity) {
        const std::string query_ = "assign a; variable haha; select such that Parent* (_,_) pattern a(\"v\", \" (x + y) * z + p \")";
        bool syntax_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SyntaxError&) {
            syntax_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntax_error_thrown);
    };

    TEST_METHOD(SemanticError_UndeclaredVariableUsedInSelect) {
        const std::string query_ = "assign a; variable haha; Select qd such that Parent* (_, _) pattern a(\"v\", \" (x + y) * z + p \")    ";
        bool semantic_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SemanticError&) {
            semantic_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(semantic_error_thrown);
    };

    TEST_METHOD(Valid_MultipleSuchthat_UsingAnd) {
        const std::string query_ = "assign a; variable haha; Select haha such that Parent* (_,_) and Parent* (_,_)";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 2);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);

    };

    TEST_METHOD(Valid_MultipleSuchthat_UsingSuchthat) {
        const std::string query_ = "assign a; variable haha; Select haha such that Parent* (_,_) such that Parent* (_,_)";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 2);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);

    };

    TEST_METHOD(Valid_MultiplePattern_UsingAnd) {
        const std::string query_ = "assign a, a1; variable haha; Select haha pattern a(_, _) and a1(_, _)";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 2);
    };

    TEST_METHOD(Valid_MultiplePattern_UsingPattern) {
        const std::string query_ = "assign a, a1; variable haha; Select haha pattern a(_, _) pattern a1(_, _)";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);

        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);

        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);

        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 2);
    };

    TEST_METHOD(Invalid_MultiplePattern_UsingAndAndPattern) {
        const std::string query_ = "assign a, a1; variable haha; Select haha pattern a(_, _) and pattern a1(_, _)";

        bool syntax_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SyntaxError&) {
            syntax_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntax_error_thrown);
    };

    TEST_METHOD(Valid_BasicIfPattern) {
        const std::string query_ = "variable v; if ifs ; Select v pattern ifs(v, _, _)";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);
        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtRefType() == RefType::kIfRef);
    };

    TEST_METHOD(Valid_BasicWhilePattern) {
        const std::string query_ = "variable v; while w ; Select v pattern w(v, _)";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);
        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 1);
        Assert::IsTrue(query->GetPatterns()->at(0)->StmtRefType() == RefType::kWhileRef);
    };

    TEST_METHOD(Valid_BasicWithClause_VarName) {
        const std::string query_ = "variable v; while w; Select v with v.varName = \" xb\" ";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);
        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
        // Check if all with clauses are correct
        Assert::IsTrue(query->GetWithClauses()->size() == 1);
        Assert::IsTrue(query->GetWithClauses()->at(0)->LhsValue() == "v");
        Assert::IsTrue(query->GetWithClauses()->at(0)->RhsValue() == "xb");
    };

    TEST_METHOD(Valid_BasicWithClause_Stmt) {
        const std::string query_ = "variable v; while w; Select v with w.stmt# = 1";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);
        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
        // Check if all with clauses are correct
        Assert::IsTrue(query->GetWithClauses()->size() == 1);
        Assert::IsTrue(query->GetWithClauses()->at(0)->LhsValue() == "w");
        Assert::IsTrue(query->GetWithClauses()->at(0)->RhsValue() == "1");
    };

    TEST_METHOD(Valid_BasicWithClause_Const) {
        const std::string query_ = "constant c; while w; Select w with c.value = 1";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);
        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
        // Check if all with clauses are correct
        Assert::IsTrue(query->GetWithClauses()->size() == 1);
        Assert::IsTrue(query->GetWithClauses()->at(0)->LhsValue() == "c");
        Assert::IsTrue(query->GetWithClauses()->at(0)->RhsValue() == "1");
    };

    TEST_METHOD(Valid_BasicWithClause_Proc) {
        const std::string query_ = "constant c; procedure p; Select p with p.procName = \" test \" ";

        shared_ptr<Query> query = query_builder_->GetQuery(query_);
        //Check if entity references are correct
        Assert::IsTrue(query->GetSelectTuple()->size() == 1);
        //Check if such that clauses are correct
        Assert::IsTrue(query->GetRelations()->size() == 0);
        //Check if all pattern clauses are correct
        Assert::IsTrue(query->GetPatterns()->size() == 0);
        // Check if all with clauses are correct
        Assert::IsTrue(query->GetWithClauses()->size() == 1);
        Assert::IsTrue(query->GetWithClauses()->at(0)->LhsValue() == "p");
        Assert::IsTrue(query->GetWithClauses()->at(0)->RhsValue() == "test");
    };

    TEST_METHOD(Invalid_RedeclarationOfSynonyms) {
        const std::string query_ = "assign a1, a2, a3; stmt s1, s2, s3; variable v1, v2, v3; variable a1; Select a1";

        bool semantic_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SemanticError&) {
            semantic_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(semantic_error_thrown);
    }

    TEST_METHOD(Invalid_SyntaticallyInvalidQuery) {
        const std::string query_ = "assign a1; Select a1 such that";
        bool syntatic_error_thrown = false;
        try {
            query_builder_->GetQuery(query_);
        }
        catch (const SyntaxError&) {
            syntatic_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntatic_error_thrown);
    }

    TEST_METHOD(Valid_BooleanSelectWithoutSynonym) {
        const std::string query_string_ = "Select BOOLEAN such that Next* (2, 9)";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);
        std::string lhs_value_ = "2";
        std::string rhs_value_ = "9";

        //Check declarations
        Assert::IsTrue(query_->GetSelectTuple()->size() == 0);
        Assert::IsTrue(query_->IsBoolean());

        //Check if such that clauses are correct
        Assert::IsTrue(query_->GetRelations()->size() == 1);
        Assert::IsTrue(query_->GetRelations()->at(0)->GetRelType() == ClauseType::kNextTRel);
        Assert::IsTrue(query_->GetRelations()->at(0)->LhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(lhs_value_, query_->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query_->GetRelations()->at(0)->ValTypes().first == ValType::kLineNum);
        Assert::IsTrue(query_->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(rhs_value_, query_->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query_->GetRelations()->at(0)->ValTypes().second == ValType::kLineNum);

        //Check if with clauses are correct
        Assert::IsTrue(query_->GetWithClauses()->size() == 0);

        //Check if pattern clauses are correct
        Assert::IsTrue(query_->GetPatterns()->size() == 0);
    }

    TEST_METHOD(Valid_BooleanSelectMultiSuchThatClause) {
        const std::string query_string_ = "assign a; Select BOOLEAN such that Next (a, 9) and Uses(a,\"x\")";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);
        std::string lhs_value_one_ = "a";
        std::string rhs_value_one_ = "9";

        std::string lhs_value_two_ = "a";
        std::string rhs_value_two_ = "x";

        //Check declarations
        Assert::IsTrue(query_->GetSelectTuple()->size() == 0);
        Assert::IsTrue(query_->IsBoolean());

        //Check if such that clauses are correct
        Assert::IsTrue(query_->GetRelations()->size() == 2);

        Assert::IsTrue(query_->GetRelations()->at(0)->GetRelType() == ClauseType::kNextRel);
        Assert::IsTrue(query_->GetRelations()->at(0)->LhsRefType() == RefType::kAssignRef);
        Assert::AreEqual(lhs_value_one_, query_->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query_->GetRelations()->at(0)->ValTypes().first == ValType::kSynonym);
        Assert::IsTrue(query_->GetRelations()->at(0)->RhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(rhs_value_one_, query_->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query_->GetRelations()->at(0)->ValTypes().second == ValType::kLineNum);

        Assert::IsTrue(query_->GetRelations()->at(1)->GetRelType() == ClauseType::kUsesSRel);
        Assert::IsTrue(query_->GetRelations()->at(1)->LhsRefType() == RefType::kAssignRef);
        Assert::AreEqual(lhs_value_two_, query_->GetRelations()->at(1)->LhsValue());
        Assert::IsTrue(query_->GetRelations()->at(1)->ValTypes().first == ValType::kSynonym);
        Assert::IsTrue(query_->GetRelations()->at(1)->RhsRefType() == RefType::kVarRef);
        Assert::AreEqual(rhs_value_two_, query_->GetRelations()->at(1)->RhsValue());
        Assert::IsTrue(query_->GetRelations()->at(1)->ValTypes().second == ValType::kVarName);

        //Check if with clauses are correct
        Assert::IsTrue(query_->GetWithClauses()->size() == 0);

        //Check if pattern clauses are correct
        Assert::IsTrue(query_->GetPatterns()->size() == 0);
    }


    TEST_METHOD(Valid_BooleanSelectUsingWith) {
        const std::string query_string_ = "variable v; Select BOOLEAN with 12 = \"number12\"";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);
        std::string lhs_value_ = "12", rhs_value_ = "number12";

        //Check declarations
        Assert::IsTrue(query_->GetSelectTuple()->size() == 0);
        Assert::IsTrue(query_->IsBoolean());

        //Check if such that clauses are correct
        Assert::IsTrue(query_->GetRelations()->size() == 0);

        //Check if with clauses are correct
        Assert::IsTrue(query_->GetWithClauses()->size() == 1);

        Assert::IsTrue(query_->GetWithClauses()->at(0)->ValTypes().first == ValType::kInt);
        Assert::IsTrue(query_->GetWithClauses()->at(0)->ValTypes().second == ValType::kString);
        Assert::IsTrue(query_->GetWithClauses()->at(0)->LhsRefType() == RefType::kUnknown);
        Assert::IsTrue(query_->GetWithClauses()->at(0)->LhsValue() == lhs_value_);
        Assert::IsTrue(query_->GetWithClauses()->at(0)->RhsValue() == rhs_value_);

        //Check if pattern clauses are correct
        Assert::IsTrue(query_->GetPatterns()->size() == 0);
    }

    TEST_METHOD(Valid_BooleanSelectDeclaredBOOLEAN) {
        const std::string query_string_ = "variable BOOLEAN; Select BOOLEAN";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);

        //Check declarations
        Assert::IsTrue(query_->GetSelectTuple()->size() == 1);
        Assert::IsTrue(!query_->IsBoolean());

        //Check if such that clauses are correct
        Assert::IsTrue(query_->GetRelations()->size() == 0);

        //Check if with clauses are correct
        Assert::IsTrue(query_->GetWithClauses()->size() == 0);

        //Check if pattern clauses are correct
        Assert::IsTrue(query_->GetPatterns()->size() == 0);
    }
    TEST_METHOD(Invalid_BooleanWithSyntaxError) {
        const std::string query_string_ = "procedure p; Select BOOLEAN with p.procName = \"12\"";
        bool syntatic_error_thrown = false;
        try {
            query_builder_->GetQuery(query_string_);
        }
        catch (const SyntaxError&) {
            syntatic_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(syntatic_error_thrown);
    }

    TEST_METHOD(Valid_MultipleClauseTypes) {
        const std::string query_string_ = "procedure p; call c; while w; procedure procName; assign a; \n\nSelect p such that Calls(\"Second\", p) and Parent(w, c) with c.procName = p.procName such that Calls* (p, \"Fifth\") with procName.procName = procName.procName pattern a(_, _\"y + z * t\"_)";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);
        std::string selectName = "p";

        //Check declarations
        Assert::IsTrue(query_->GetSelectTuple()->size() == 1);

        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetRefType() == RefType::kProcRef);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query_->GetSelectTuple()->at(0)->GetName(), selectName);

        //Check if such that clauses are correct
        Assert::IsTrue(query_->GetRelations()->size() == 3);

        std::string rel_lhs_one_ = "Second";
        std::string rel_rhs_one_ = "p";
        Assert::IsTrue(query_->GetRelations()->at(0)->GetRelType() == ClauseType::kCallsRel);
        Assert::IsTrue(query_->GetRelations()->at(0)->LhsRefType() == RefType::kProcRef);
        Assert::AreEqual(rel_lhs_one_, query_->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query_->GetRelations()->at(0)->ValTypes().first == ValType::kProcName);
        Assert::IsTrue(query_->GetRelations()->at(0)->RhsRefType() == RefType::kProcRef);
        Assert::AreEqual(rel_rhs_one_, query_->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query_->GetRelations()->at(0)->ValTypes().second == ValType::kSynonym);

        std::string rel_lhs_two_ = "w";
        std::string rel_rhs_two_ = "c";
        Assert::IsTrue(query_->GetRelations()->at(1)->GetRelType() == ClauseType::kParentRel);
        Assert::IsTrue(query_->GetRelations()->at(1)->LhsRefType() == RefType::kWhileRef);
        Assert::AreEqual(rel_lhs_two_, query_->GetRelations()->at(1)->LhsValue());
        Assert::IsTrue(query_->GetRelations()->at(1)->ValTypes().first == ValType::kSynonym);
        Assert::IsTrue(query_->GetRelations()->at(1)->RhsRefType() == RefType::kCallRef);
        Assert::AreEqual(rel_rhs_two_, query_->GetRelations()->at(1)->RhsValue());
        Assert::IsTrue(query_->GetRelations()->at(1)->ValTypes().second == ValType::kSynonym);


        std::string rel_lhs_three_ = "p";
        std::string rel_rhs_three_ = "Fifth";
        Assert::IsTrue(query_->GetRelations()->at(2)->GetRelType() == ClauseType::kCallsTRel);
        Assert::IsTrue(query_->GetRelations()->at(2)->LhsRefType() == RefType::kProcRef);
        Assert::AreEqual(rel_lhs_three_, query_->GetRelations()->at(2)->LhsValue());
        Assert::IsTrue(query_->GetRelations()->at(2)->ValTypes().first == ValType::kSynonym);
        Assert::IsTrue(query_->GetRelations()->at(2)->RhsRefType() == RefType::kProcRef);
        Assert::AreEqual(rel_rhs_three_, query_->GetRelations()->at(2)->RhsValue());
        Assert::IsTrue(query_->GetRelations()->at(2)->ValTypes().second == ValType::kProcName);

        //Check if with clauses are correct - INCOMPLETE FEATURE - PLEASE UPDATE 

        //Check if Pattern Clauses are correct
        Assert::IsTrue(query_->GetPatterns()->size() == 1);

        const std::string select_variable = "a";
        std::string expr_str = "y + z * t";
        Assert::IsTrue(query_->GetPatterns()->at(0)->VarValType() == ValType::kWildcard);
        Assert::IsTrue(query_->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::AreEqual(select_variable, query_->GetPatterns()->at(0)->StmtSyn());
        Assert::IsTrue(query_->GetPatterns()->at(0)->GetPatternType() == ClauseType::kAssignPattern);
        Assert::AreEqual(expr_str, query_->GetPatterns()->at(0)->GetExprSpec()->GetInfix());
        Assert::IsTrue(query_->GetPatterns()->at(0)->GetExprSpec()->IsWildcard() != true);
        Assert::IsTrue(query_->GetPatterns()->at(0)->StmtRefType() == RefType::kAssignRef);
        Assert::IsTrue(query_->GetPatterns()->at(0)->VarValType() == ValType::kWildcard);

    }

    TEST_METHOD(Invalid_MultipleClauseTypes) {
        const std::string query_string_ = "procedure p; call c; Select p with c.procName = p.procName and such that Calls(p,p)";

        bool semantic_error_thrown = false;
        try {
            query_builder_->GetQuery(query_string_);
        }
        catch (const SemanticError&) {
            semantic_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(semantic_error_thrown);
    }

    TEST_METHOD(Valid_WhilePatternMultipleReturn) {
        const std::string query_string_ = "variable v; assign a; while w; Select <a, v> pattern w(v,_) such that Calls(\"Second\", \"Third\") such that Affects* (a, 10) and Affects(11,12)";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);

        //Check declarations
        Assert::IsTrue(query_->GetSelectTuple()->size() == 2);

        std::string select_name_one_ = "a";
        std::string select_name_two_ = "v";

        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetRefType() == RefType::kAssignRef);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query_->GetSelectTuple()->at(0)->GetName(), select_name_one_);

        Assert::IsTrue(query_->GetSelectTuple()->at(1)->GetRefType() == RefType::kVarRef);
        Assert::IsTrue(query_->GetSelectTuple()->at(1)->GetValType() == ValType::kSynonym);
        Assert::AreEqual(query_->GetSelectTuple()->at(1)->GetName(), select_name_two_);

        //Check if such that clauses are correct
        Assert::IsTrue(query_->GetRelations()->size() == 3);

        std::string rel_lhs_one_ = "Second";
        std::string rel_rhs_one_ = "Third";
        Assert::IsTrue(query_->GetRelations()->at(0)->GetRelType() == ClauseType::kCallsRel);
        Assert::IsTrue(query_->GetRelations()->at(0)->LhsRefType() == RefType::kProcRef);
        Assert::AreEqual(rel_lhs_one_, query_->GetRelations()->at(0)->LhsValue());
        Assert::IsTrue(query_->GetRelations()->at(0)->ValTypes().first == ValType::kProcName);
        Assert::IsTrue(query_->GetRelations()->at(0)->RhsRefType() == RefType::kProcRef);
        Assert::AreEqual(rel_rhs_one_, query_->GetRelations()->at(0)->RhsValue());
        Assert::IsTrue(query_->GetRelations()->at(0)->ValTypes().second == ValType::kProcName);

        std::string rel_lhs_two_ = "a";
        std::string rel_rhs_two_ = "10";
        Assert::IsTrue(query_->GetRelations()->at(1)->GetRelType() == ClauseType::kAffectsTRel);
        Assert::IsTrue(query_->GetRelations()->at(1)->LhsRefType() == RefType::kAssignRef);
        Assert::AreEqual(rel_lhs_two_, query_->GetRelations()->at(1)->LhsValue());
        Assert::IsTrue(query_->GetRelations()->at(1)->ValTypes().first == ValType::kSynonym);
        Assert::IsTrue(query_->GetRelations()->at(1)->RhsRefType() == RefType::kStmtRef);
        Assert::AreEqual(rel_rhs_two_, query_->GetRelations()->at(1)->RhsValue());
        Assert::IsTrue(query_->GetRelations()->at(1)->ValTypes().second == ValType::kLineNum);



        //Check if Pattern Clauses are correct
        Assert::IsTrue(query_->GetPatterns()->size() == 1);

        //Check if with clauses are correct
        Assert::IsTrue(query_->GetWithClauses()->size() == 0);

        const std::string select_variable = "w";
        std::string expr_str = "";
        Assert::IsTrue(query_->GetPatterns()->at(0)->VarValType() == ValType::kSynonym);
        Assert::IsTrue(query_->GetPatterns()->at(0)->StmtValType() == ValType::kSynonym);
        Assert::AreEqual(select_variable, query_->GetPatterns()->at(0)->StmtSyn());
        Assert::IsTrue(query_->GetPatterns()->at(0)->GetPatternType() == ClauseType::kWhilePattern);
        Assert::IsTrue(query_->GetPatterns()->at(0)->StmtRefType() == RefType::kWhileRef);
        Assert::IsTrue(query_->GetPatterns()->at(0)->VarValType() == ValType::kSynonym);

    }


    TEST_METHOD(Invalid_IfsPattern) {
        const std::string query_string_ = "procedure p; call c; if ifs;variable v; Select p with c.procName = p.procName and such that Calls(p,p) pattern ifs(v,_,v)";

        bool semantic_error_thrown = false;
        try {
            query_builder_->GetQuery(query_string_);
        }
        catch (const SemanticError&) {
            semantic_error_thrown = true;
        }
        catch (...) {
        }
        Assert::IsTrue(semantic_error_thrown);
    }

    TEST_METHOD(Valid_Select_Single_Attr_Proc) {
        const std::string query_string_ = "procedure p1; Select p1.procName with p1.procName = \"findPrimes\"";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);

        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetRefType() == RefType::kProcRef);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetAttrType() == AttrType::kProcName);
    }

    TEST_METHOD(Valid_Select_Single_Attr_Var) {
        const std::string query_string_ = "procedure p1; variable v; Select v.varName with p1.procName = \"findPrimes\"";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);

        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetRefType() == RefType::kVarRef);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetAttrType() == AttrType::kVarName);
    }

    TEST_METHOD(Valid_Select_Single_Attr_Call_ProcName) {
        const std::string query_string_ = "procedure p1; call c; Select c.procName with p1.procName = \"findPrimes\"";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);

        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetRefType() == RefType::kCallRef);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetAttrType() == AttrType::kProcName);
    }

    TEST_METHOD(Valid_Select_Single_Attr_Call_StmtNum) {
        const std::string query_string_ = "procedure p1; call c; Select c.stmt# with p1.procName = \"findPrimes\"";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);

        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetRefType() == RefType::kCallRef);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetAttrType() == AttrType::kStmtNum);
    }

    TEST_METHOD(Valid_Select_Multiple_Attr) {
        const std::string query_string_ = "procedure p1; call c; Select <c.stmt#, p1.procName> with p1.procName = \"findPrimes\"";
        shared_ptr<Query> query_ = query_builder_->GetQuery(query_string_);

        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetRefType() == RefType::kCallRef);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetValType() == ValType::kSynonym);
        Assert::IsTrue(query_->GetSelectTuple()->at(0)->GetAttrType() == AttrType::kStmtNum);

        Assert::IsTrue(query_->GetSelectTuple()->at(1)->GetRefType() == RefType::kProcRef);
        Assert::IsTrue(query_->GetSelectTuple()->at(1)->GetValType() == ValType::kSynonym);
        Assert::IsTrue(query_->GetSelectTuple()->at(1)->GetAttrType() == AttrType::kProcName);
    }
    };
}