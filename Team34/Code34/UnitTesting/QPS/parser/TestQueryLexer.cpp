#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>

#include "../SPA/QPS/parser/QueryLexer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{
	TEST_CLASS(TestBasicQueryLexer)
	{
	private:
		std::shared_ptr<QueryLexer> query_lexer_ = std::make_shared<QueryLexer>();
	public:
		TEST_METHOD(TestQueryLexerParseInteger) {

			const std::string query_ = "variable V; Select V such that Uses(357,V)";
			const std::string identity_ = "V";
			const std::string reference_keyword_ = "Uses";
			this->query_lexer_->FeedQuery(query_);

			Assert::IsTrue(this->query_lexer_->HasDesignEntity());
			this->query_lexer_->MatchDesignEntityKeyword();
			Assert::IsTrue(this->query_lexer_->HasIdentity());
			Assert::AreEqual(identity_, this->query_lexer_->MatchIdentity());
			Assert::IsTrue(this->query_lexer_->HasEndOfDeclarationStatement());
			this->query_lexer_->MatchEndOfDeclarationStatement();
			Assert::IsTrue(this->query_lexer_->HasKeyword("Select"));
			this->query_lexer_->MatchKeyword("Select");
			Assert::IsTrue(this->query_lexer_->HasIdentity());
			Assert::AreEqual(identity_, this->query_lexer_->MatchIdentity());
			Assert::IsTrue(this->query_lexer_->HasKeyword("such"));
			this->query_lexer_->MatchKeyword("such");
			Assert::IsTrue(this->query_lexer_->HasKeyword("that"));
			this->query_lexer_->MatchKeyword("that");
			Assert::IsTrue(this->query_lexer_->HasReferenceKeyword());
			Assert::AreEqual( reference_keyword_, this->query_lexer_->MatchReferenceKeyword());
			Assert::IsTrue(this->query_lexer_->HasOpeningBrace());
			this->query_lexer_->MatchOpeningBrace();
			Assert::IsTrue(this->query_lexer_->HasInteger());
			Assert::AreEqual(357,this->query_lexer_->MatchInteger());
			Assert::IsTrue(this->query_lexer_->HasCommaDelimeter());
			this->query_lexer_->MatchCommaDelimeter();
			Assert::IsTrue(this->query_lexer_->HasIdentity());
			Assert::AreEqual(identity_, this->query_lexer_->MatchIdentity());
			Assert::IsTrue(this->query_lexer_->HasClosingBrace());
			this->query_lexer_->MatchClosingBrace();
			Assert::IsTrue(!this->query_lexer_->HasMoreTokens());
		};
	};
}