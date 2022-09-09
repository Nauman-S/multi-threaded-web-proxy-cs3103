#include "QueryLexer.h"
#include "../reference/EntityRef.h"
#include <algorithm>

void QueryLexer::InitializeKeywords() {
	this->relation_keywords_.insert({ "FOLLOWS", "FOLLOWS*", "PARENT", "PARENT*", "USES", "MODIFIES" });
	this->design_entities_.insert({ EntityRef::kStmt, EntityRef::kRead, EntityRef::kPrint, EntityRef::kCall, EntityRef::kWhile,
		EntityRef::kIf, EntityRef::kAssign, EntityRef::kVariable, EntityRef::kConstant, EntityRef::kProcedure });
	this->keywords_.insert({ "SELECT", "SUCH", "THAT" });
	this->delimiters_.insert({ ';',',','(',')','\"' });
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
		transform(sval_.begin(), sval_.end(), sval_.begin(), ::toupper);
		if (this->design_entities_.find(sval_) != this->design_entities_.end()) {
			return true;
		}
	}
	return false;
}

std::string QueryLexer::MatchDesignEntityKeyword() {
	if (!HasDesignEntity()) throw SyntaxError(GenerateErrorMessage("design entity keyword", tokenizer_->getTokenSval().value_or("INTEGER")));
	std::string sval_ = this->tokenizer_->getTokenSval().value();
	transform(sval_.begin(), sval_.end(), sval_.begin(), ::toupper);
	this->tokenizer_->nextToken();
	return sval_;
}

bool QueryLexer::HasIdentity() {
	return this->tokenizer_->getToken().type_ == TokenType::kName;
}

std::string QueryLexer::MatchIdentity() {
	if (!HasIdentity()) throw SyntaxError(GenerateErrorMessage("IDENTITY", tokenizer_->getTokenSval().value_or("INTEGER")));
	std::string sval_ = this->tokenizer_->getTokenSval().value();
	transform(sval_.begin(), sval_.end(), sval_.begin(), ::toupper);
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
		transform(sval_.begin(), sval_.end(), sval_.begin(), ::toupper);
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
		transform(sval_.begin(), sval_.end(), sval_.begin(), ::toupper);
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
	transform(sval_.begin(), sval_.end(), sval_.begin(), ::toupper);
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

int QueryLexer::MatchInteger() {
	if (!HasInteger()) throw SyntaxError(GenerateErrorMessage("INTEGER", tokenizer_->getTokenSval().value_or("INTEGER")));
	int i = this->tokenizer_->getTokenIval().value();
	this->tokenizer_->nextToken();
	return i;
}

bool QueryLexer::HasPatternKeyword() {
	if (this->tokenizer_->getToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->getTokenSval().value();
		transform(sval_.begin(), sval_.end(), sval_.begin(), ::toupper);
		return sval_.compare("PATTERN") == 0;
	}
	return false;
}

std::string QueryLexer::MatchPatternKeyword() {
	if (!HasPatternKeyword()) throw SyntaxError(GenerateErrorMessage("Pattern", tokenizer_->getTokenSval().value_or("INTEGER")));

	this->tokenizer_->nextToken();
	return "PATTERN";
}

bool QueryLexer::HasMoreTokens() {
	return this->tokenizer_->getToken().type_ != TokenType::kParseEnd;
}



string QueryLexer::GenerateErrorMessage(string expected, string actual) {
	return "Expected Token: " + expected + " ; Actual Token: " + actual;
};