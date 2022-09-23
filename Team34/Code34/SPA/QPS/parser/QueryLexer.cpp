#include "QueryLexer.h"
#include <algorithm>

#include "../reference/EntityRef.h"

void QueryLexer::InitializeKeywords() {
	this->relation_keywords_.insert({ "Follows", "Follows*", "Parent", "Parent*", "Uses", "Modifies" });
	this->design_entities_.insert({ EntityRef::kStmt, EntityRef::kRead, EntityRef::kPrint, EntityRef::kCall, EntityRef::kWhile,
		EntityRef::kIf, EntityRef::kAssign, EntityRef::kVariable, EntityRef::kConstant, EntityRef::kProcedure });
	this->keywords_.insert({ "Select", "such", "that" });
	this->delimiters_.insert({ ';',',','(',')','\"' });
	this->operators_.insert({TokenType::kAdd, TokenType::kMinus, TokenType::kkDivide, TokenType::kMultiply,TokenType::kModulo});
}

QueryLexer::QueryLexer() {
	InitializeKeywords();
	this->tokenizer_ = new Tokenizer();
}

QueryLexer::~QueryLexer() {
	delete this->tokenizer_;
}

void QueryLexer::FeedQuery(const std::string& query_string) {
	this->tokenizer_->feedLine(query_string);
	this->tokenizer_->nextToken();
}

bool QueryLexer::HasDesignEntity() {
	if (this->tokenizer_->getToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->getTokenSval().value();
		if (this->design_entities_.find(sval_) != this->design_entities_.end()) {
			return true;
		}
	}
	return false;
}

std::string QueryLexer::MatchDesignEntityKeyword() {
	if (!HasDesignEntity()) throw SyntaxError(GenerateErrorMessage("design entity keyword", tokenizer_->getTokenSval().value_or("INTEGER")));
	std::string sval_ = this->tokenizer_->getTokenSval().value();
	this->tokenizer_->nextToken();
	return sval_;
}

bool QueryLexer::HasIdentity() {
	return this->tokenizer_->getToken().type_ == TokenType::kName;
}

std::string QueryLexer::MatchIdentity() {
	if (!HasIdentity()) throw SyntaxError(GenerateErrorMessage("IDENTITY", tokenizer_->getTokenSval().value_or("INTEGER")));
	std::string sval_ = this->tokenizer_->getTokenSval().value();
	this->tokenizer_->nextToken();
	return sval_;
}

bool QueryLexer::HasEndOfDeclarationStatement() {
	return this->tokenizer_->getToken().type_ == TokenType::kSemiColon;
}

std::string QueryLexer::MatchEndOfDeclarationStatement() {
	if (!HasEndOfDeclarationStatement()) throw SyntaxError(GenerateErrorMessage(";", tokenizer_->getTokenSval().value_or("INTEGER")));
	this->tokenizer_->nextToken();
	return ";";
}

bool QueryLexer::HasKeyword(std::string keyword_) {
	if (this->tokenizer_->getToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->getTokenSval().value();
		return this->keywords_.find(sval_) != this->keywords_.end() && sval_.compare(keyword_) == 0;
	}
	return false;
}

void QueryLexer::MatchKeyword(std::string keyword_) {
	if (!HasKeyword(keyword_)) throw SyntaxError(GenerateErrorMessage(keyword_, tokenizer_->getTokenSval().value_or("INTEGER")));
	this->tokenizer_->nextToken();
}


bool QueryLexer::HasReferenceKeyword() {
	if (this->tokenizer_->getToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->getTokenSval().value();
		if (this->relation_keywords_.find(sval_) != this->relation_keywords_.end()) {
			return true;
		}
	}
	return false;
}

std::string QueryLexer::MatchReferenceKeyword() {
	if (!HasReferenceKeyword()) throw SyntaxError(GenerateErrorMessage("ReferenceKeyword", tokenizer_->getTokenSval().value_or("INTEGER")));
	std::string sval_ = this->tokenizer_->getTokenSval().value();
	this->tokenizer_->nextToken();
	if (this->tokenizer_->getToken().type_ == TokenType::kMultiply) {
		sval_.push_back('*');
		this->tokenizer_->nextToken();
	}

	return sval_;
}

//conintue below here

bool QueryLexer::HasOpeningBrace() {
	return this->tokenizer_->getToken().type_ == TokenType::kLeftRound;
}

std::string QueryLexer::MatchOpeningBrace() {
	if (!HasOpeningBrace()) throw SyntaxError(GenerateErrorMessage("(", tokenizer_->getTokenSval().value_or("INTEGER")));
	this->tokenizer_->nextToken();
	return "(";
}

bool QueryLexer::HasClosingBrace() {
	return this->tokenizer_->getToken().type_ == TokenType::kRightRound;
}

std::string QueryLexer::MatchClosingBrace() {
	if (!HasClosingBrace()) throw SyntaxError(GenerateErrorMessage(")", tokenizer_->getTokenSval().value_or("INTEGER")));
	this->tokenizer_->nextToken();
	return ")";
}

bool QueryLexer::HasUnderScore() {
	return this->tokenizer_->getToken().type_ == TokenType::kUnderscore;
}

void QueryLexer::MatchUnderScore() {
	if (!HasUnderScore()) throw SyntaxError(GenerateErrorMessage("_", tokenizer_->getTokenSval().value_or("INTEGER")));
	this->tokenizer_->nextToken();
}

bool QueryLexer::HasQuotationMarks() {
	return this->tokenizer_->getToken().type_ == TokenType::kDoubleQuote || this->tokenizer_->getToken().type_ == TokenType::kSingleQuote;
}

void QueryLexer::MatchQuotationMarks() {
	if (!HasQuotationMarks()) throw SyntaxError(GenerateErrorMessage("\"", tokenizer_->getTokenSval().value_or("INTEGER")));
	this->tokenizer_->nextToken();
}

bool QueryLexer::HasCommaDelimeter() {
	return this->tokenizer_->getToken().type_ == TokenType::kComma;
}

std::string QueryLexer::MatchCommaDelimeter() {
	if (!HasCommaDelimeter()) throw SyntaxError(GenerateErrorMessage(",", tokenizer_->getTokenSval().value_or("INTEGER")));
	this->tokenizer_->nextToken();
	return ",";
}

bool QueryLexer::HasInteger() {
	return this->tokenizer_->getToken().type_ == TokenType::kInteger;
}

bool QueryLexer::HasOperator() {
	return this->operators_.find(this->tokenizer_->getToken().type_) != this->operators_.end();
}

std::string QueryLexer::MatchOperator() {
	std::string operator_string_;
		if (this->tokenizer_->getToken().type_ == TokenType::kAdd) {
			operator_string_ = "+";
		}
		else if (this->tokenizer_->getToken().type_ == TokenType::kMinus) {
			operator_string_ = "-";
		}
		else if (this->tokenizer_->getToken().type_ == TokenType::kkDivide) {
			operator_string_ = "/";
		}
		else if (this->tokenizer_->getToken().type_ == TokenType::kMultiply) {
			operator_string_ = "*";
		}
		else if (this->tokenizer_->getToken().type_ == TokenType::kModulo) {
			operator_string_ = "%";
		}

		this->tokenizer_->nextToken();
		return operator_string_;
}
int QueryLexer::MatchInteger() {
	if (!HasInteger()) throw SyntaxError(GenerateErrorMessage("INTEGER", tokenizer_->getTokenSval().value_or("INTEGER")));
	int i = this->tokenizer_->getTokenIval().value();
	this->tokenizer_->nextToken();
	return i;
}

bool QueryLexer::HasPatternKeyword() {
	if (this->tokenizer_->getToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->getTokenSval().value();
		return sval_.compare("pattern") == 0;
	}
	return false;
}

std::string QueryLexer::MatchPatternKeyword() {
	if (!HasPatternKeyword()) throw SyntaxError(GenerateErrorMessage("Pattern", tokenizer_->getTokenSval().value_or("INTEGER")));

	this->tokenizer_->nextToken();
	return "pattern";
}

bool QueryLexer::HasAndKeyword() {
	if (this->tokenizer_->getToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->getTokenSval().value();
		return sval_.compare("and") == 0;
	}
	return false;
}

void QueryLexer::MatchAndKeyword() {
	if (!HasAndKeyword()) throw SyntaxError(GenerateErrorMessage("and", tokenizer_->getTokenSval().value_or("INTEGER")));

	this->tokenizer_->nextToken();
}

bool QueryLexer::HasMoreTokens() {
	return this->tokenizer_->getToken().type_ != TokenType::kParseEnd;
}

bool QueryLexer::HasSuchThatKeywords() {
	return HasKeyword("such") && (PeekNextToken(1) == "that");
}

void QueryLexer::MatchSuchThatKeywords() {
	MatchKeyword("such");
	MatchKeyword("that");
}

string QueryLexer::GenerateErrorMessage(string expected, string actual) {
	return "Expected Token: " + expected + " ; Actual Token: " + actual;
};

std::string QueryLexer::PeekNextToken(int number_tokens_) {
	return this->tokenizer_->PeekNextToken(number_tokens_);
}

