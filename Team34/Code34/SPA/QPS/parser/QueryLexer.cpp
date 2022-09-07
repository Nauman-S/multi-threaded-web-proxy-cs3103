#include "QueryLexer.h"
#include <algorithm>

void QueryLexer::InitializeKeywords() {
	this->relation_keywords_.insert({ "FOLLOWS", "FOLLOWS*", "PARENT", "PARENT*", "USES", "MODIFIES" });
	this->design_entities_.insert({ "STMT", "READ", "PRINT", "CALL", "WHILE", "IF", "ASSIGN", "VARIABLE", "CONSTANT", "PROCEDURE" });
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
	std::string sval_ = this->tokenizer_->getTokenSval().value();
	transform(sval_.begin(), sval_.end(), sval_.begin(), ::toupper);
	this->tokenizer_->nextToken();
	return sval_;
}

bool QueryLexer::HasIdentity() {
	return this->tokenizer_->getToken().type_ == TokenType::kName;
}

std::string QueryLexer::MatchIdentity() {
	std::string sval_ = this->tokenizer_->getTokenSval().value();
	transform(sval_.begin(), sval_.end(), sval_.begin(), ::toupper);
	this->tokenizer_->nextToken();
	return sval_;
}

bool QueryLexer::HasEndOfDeclarationStatement() {
	return this->tokenizer_->getToken().type_ == TokenType::kSemiColon;
}

std::string QueryLexer::MatchEndOfDeclarationStatement() {
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

void QueryLexer::MatchKeyword() {
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
	this->tokenizer_->nextToken();
	return "(";
}

bool QueryLexer::HasClosingBrace() {
	return this->tokenizer_->getToken().type_ == TokenType::kRightRound;
}

std::string QueryLexer::MatchClosingBrace() {
	this->tokenizer_->nextToken();
	return ")";
}

bool QueryLexer::HasUnderScore() {
	return this->tokenizer_->getToken().type_ == TokenType::kUnderscore;
}

void QueryLexer::MatchUnderScore() {
	this->tokenizer_->nextToken();
}

bool QueryLexer::HasQuotationMarks() {
	return this->tokenizer_->getToken().type_ == TokenType::kDoubleQuote || this->tokenizer_->getToken().type_ == TokenType::kSingleQuote;
}

void QueryLexer::MatchQuotationMarks() {
	this->tokenizer_->nextToken();
}

bool QueryLexer::HasCommaDelimeter() {
	return this->tokenizer_->getToken().type_ == TokenType::kComma;
}

std::string QueryLexer::MatchCommaDelimeter() {
	this->tokenizer_->nextToken();
	return ",";
}

bool QueryLexer::HasInteger() {
	return this->tokenizer_->getToken().type_ == TokenType::kInteger;
}

int QueryLexer::MatchInteger() {
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
	this->tokenizer_->nextToken();
	return "PATTERN";
}

bool QueryLexer::HasMoreTokens() {
	return this->tokenizer_->getToken().type_ != TokenType::kParseEnd;
}