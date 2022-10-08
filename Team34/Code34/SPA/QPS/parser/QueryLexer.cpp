#include "QueryLexer.h"
#include <algorithm>

#include "../reference/EntityRef.h"

void QueryLexer::InitializeKeywords() {
	this->relation_keywords_.insert({ "Follows", "Follows*", "Parent", "Parent*", "Uses", "Modifies", 
		"Next", "Next*", "Calls", "Calls*", "Affects", "Affects*"});
	this->design_entities_.insert({ EntityRef::kStmt, EntityRef::kRead, EntityRef::kPrint, EntityRef::kCall, EntityRef::kWhile,
		EntityRef::kIf, EntityRef::kAssign, EntityRef::kVariable, EntityRef::kConstant, EntityRef::kProcedure });
	this->keywords_.insert({ "Select", "such", "that", "BOOLEAN"});
	attr_names_.insert({ "procName", "varName", "value", "stmt" });
	this->delimiters_.insert({ ';',',','(',')','\"', '<', '>', '.'});
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
	this->tokenizer_->FeedLine(query_string);
	this->tokenizer_->NextToken();
}

bool QueryLexer::HasDesignEntity() {
	if (this->tokenizer_->GetToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->GetTokenSval().value();
		if (this->design_entities_.find(sval_) != this->design_entities_.end()) {
			return true;
		}
	}
	return false;
}

std::string QueryLexer::MatchDesignEntityKeyword() {
	if (!HasDesignEntity()) throw SyntaxError(GenerateErrorMessage("design entity keyword", tokenizer_->GetTokenSval().value_or("INTEGER")));
	std::string sval_ = this->tokenizer_->GetTokenSval().value();
	this->tokenizer_->NextToken();
	return sval_;
}

bool QueryLexer::HasIdentity() {
	return this->tokenizer_->GetToken().type_ == TokenType::kName;
}

std::string QueryLexer::MatchIdentity() {
	if (!HasIdentity()) throw SyntaxError(GenerateErrorMessage("IDENTITY", tokenizer_->GetTokenSval().value_or("INTEGER")));
	std::string sval_ = this->tokenizer_->GetTokenSval().value();
	this->tokenizer_->NextToken();
	return sval_;
}

bool QueryLexer::HasEndOfDeclarationStatement() {
	return this->tokenizer_->GetToken().type_ == TokenType::kSemiColon;
}

std::string QueryLexer::MatchEndOfDeclarationStatement() {
	if (!HasEndOfDeclarationStatement()) throw SyntaxError(GenerateErrorMessage(";", tokenizer_->GetTokenSval().value_or("INTEGER")));
	this->tokenizer_->NextToken();
	return ";";
}

bool QueryLexer::HasKeyword(std::string keyword_) {
	if (this->tokenizer_->GetToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->GetTokenSval().value();
		return this->keywords_.find(sval_) != this->keywords_.end() && sval_.compare(keyword_) == 0;
	}
	return false;
}

void QueryLexer::MatchKeyword(std::string keyword_) {
	if (!HasKeyword(keyword_)) throw SyntaxError(GenerateErrorMessage(keyword_, tokenizer_->GetTokenSval().value_or("INTEGER")));
	this->tokenizer_->NextToken();
}


bool QueryLexer::HasReferenceKeyword() {
	if (this->tokenizer_->GetToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->GetTokenSval().value();
		if (this->relation_keywords_.find(sval_) != this->relation_keywords_.end()) {
			return true;
		}
	}
	return false;
}

std::string QueryLexer::MatchReferenceKeyword() {
	if (!HasReferenceKeyword()) throw SyntaxError(GenerateErrorMessage("ReferenceKeyword", tokenizer_->GetTokenSval().value_or("INTEGER")));
	std::string sval_ = this->tokenizer_->GetTokenSval().value();
	this->tokenizer_->NextToken();
	if (this->tokenizer_->GetToken().type_ == TokenType::kMultiply) {
		sval_.push_back('*');
		this->tokenizer_->NextToken();
	}

	return sval_;
}


bool QueryLexer::HasLeftBrace() {
	return this->tokenizer_->GetToken().type_ == TokenType::kLeftRound;
}

void QueryLexer::MatchLeftBrace() {
	if (!HasLeftBrace()) throw SyntaxError(GenerateErrorMessage("(", tokenizer_->GetTokenSval().value_or("INTEGER")));
	tokenizer_->NextToken();
}

bool QueryLexer::HasRightBrace() {
	return this->tokenizer_->GetToken().type_ == TokenType::kRightRound;
}

void QueryLexer::MatchRightBrace() {
	if (!HasRightBrace()) throw SyntaxError(GenerateErrorMessage(")", tokenizer_->GetTokenSval().value_or("INTEGER")));
	tokenizer_->NextToken();
}

bool QueryLexer::HasLeftAngle() {
	return this->tokenizer_->GetToken().type_ == TokenType::kLesser;
}

void QueryLexer::MatchLeftAngle() {
	if (!HasLeftAngle()) throw SyntaxError(GenerateErrorMessage("<", tokenizer_->GetTokenSval().value_or("INTEGER")));
	tokenizer_->NextToken();
}

bool QueryLexer::HasRightAngle() {
	return this->tokenizer_->GetToken().type_ == TokenType::kGreater;
}

void QueryLexer::MatchRightAngle() {
	if (!HasRightAngle()) throw SyntaxError(GenerateErrorMessage(">", tokenizer_->GetTokenSval().value_or("INTEGER")));
	tokenizer_->NextToken();
}

bool QueryLexer::HasUnderScore() {
	return tokenizer_->GetToken().type_ == TokenType::kUnderscore;
}

void QueryLexer::MatchUnderScore() {
	if (!HasUnderScore()) throw SyntaxError(GenerateErrorMessage("_", tokenizer_->GetTokenSval().value_or("INTEGER")));
	tokenizer_->NextToken();
}

bool QueryLexer::HasFullStop() {
	return tokenizer_->GetToken().type_ == TokenType::kFullStop;
}

void QueryLexer::MatchFullStop() {
	if (!HasFullStop()) throw SyntaxError(GenerateErrorMessage(".", tokenizer_->GetTokenSval().value_or("INTEGER")));
	tokenizer_->NextToken();
}

bool QueryLexer::HasEqualSign() {
	return tokenizer_->GetToken().type_ == TokenType::kEqual;
}

void QueryLexer::MatchEqualSign() {
	if (!HasEqualSign()) throw SyntaxError(GenerateErrorMessage("=", tokenizer_->GetTokenSval().value_or("INTEGER")));
	tokenizer_->NextToken();
}

bool QueryLexer::HasQuotationMarks() {
	return this->tokenizer_->GetToken().type_ == TokenType::kDoubleQuote || this->tokenizer_->GetToken().type_ == TokenType::kSingleQuote;
}

void QueryLexer::MatchQuotationMarks() {
	if (!HasQuotationMarks()) throw SyntaxError(GenerateErrorMessage("\"", tokenizer_->GetTokenSval().value_or("INTEGER")));
	this->tokenizer_->NextToken();
}

bool QueryLexer::HasComma() {
	return this->tokenizer_->GetToken().type_ == TokenType::kComma;
}

void QueryLexer::MatchComma() {
	if (!HasComma()) throw SyntaxError(GenerateErrorMessage(",", tokenizer_->GetTokenSval().value_or("INTEGER")));
	tokenizer_->NextToken();
}

bool QueryLexer::HasHashtag() {
	return this->tokenizer_->GetToken().type_ == TokenType::kHashtag;
}

void QueryLexer::MatchHashtag() {
	if (!HasHashtag()) throw SyntaxError(GenerateErrorMessage("#", tokenizer_->GetTokenSval().value_or("INTEGER")));
	tokenizer_->NextToken();
}

bool QueryLexer::HasInteger() {
	return this->tokenizer_->GetToken().type_ == TokenType::kInteger;
}

bool QueryLexer::HasOperator() {
	return this->operators_.find(this->tokenizer_->GetToken().type_) != this->operators_.end();
}

std::string QueryLexer::MatchOperator() {
	std::string operator_string_;
		if (tokenizer_->GetToken().type_ == TokenType::kAdd) {
			operator_string_ = "+";
		}
		else if (tokenizer_->GetToken().type_ == TokenType::kMinus) {
			operator_string_ = "-";
		}
		else if (tokenizer_->GetToken().type_ == TokenType::kkDivide) {
			operator_string_ = "/";
		}
		else if (tokenizer_->GetToken().type_ == TokenType::kMultiply) {
			operator_string_ = "*";
		}
		else if (tokenizer_->GetToken().type_ == TokenType::kModulo) {
			operator_string_ = "%";
		} 
		this->tokenizer_->NextToken();
		return operator_string_;
}
int QueryLexer::MatchInteger() {
	if (!HasInteger()) throw SyntaxError(GenerateErrorMessage("INTEGER", tokenizer_->GetTokenSval().value_or("INTEGER")));
	int i = this->tokenizer_->GetTokenIval().value();
	this->tokenizer_->NextToken();
	return i;
}

bool QueryLexer::HasPatternKeyword() {
	if (this->tokenizer_->GetToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->GetTokenSval().value();
		return sval_.compare("pattern") == 0;
	}
	return false;
}

void QueryLexer::MatchPatternKeyword() {
	if (!HasPatternKeyword()) throw SyntaxError(GenerateErrorMessage("pattern", tokenizer_->GetTokenSval().value_or("INTEGER")));
	this->tokenizer_->NextToken();
}

bool QueryLexer::HasWithKeyword() {
	if (this->tokenizer_->GetToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->GetTokenSval().value();
		return sval_.compare("with") == 0;
	}
	return false;
}

void QueryLexer::MatchWithKeyword() {
	if (!HasWithKeyword()) throw SyntaxError(GenerateErrorMessage("with", tokenizer_->GetTokenSval().value_or("INTEGER")));
	this->tokenizer_->NextToken();
}


bool QueryLexer::HasAndKeyword() {
	if (this->tokenizer_->GetToken().type_ == TokenType::kName) {
		std::string sval_ = this->tokenizer_->GetTokenSval().value();
		return sval_.compare("and") == 0;
	}
	return false;
}

void QueryLexer::MatchAndKeyword() {
	if (!HasAndKeyword()) throw SyntaxError(GenerateErrorMessage("and", tokenizer_->GetTokenSval().value_or("INTEGER")));
	this->tokenizer_->NextToken();
}


bool QueryLexer::HasBooleanKeyword() {
	if (this->tokenizer_->GetToken().type_ != TokenType::kName) {
		return false;
	}
	std::string sval_ = tokenizer_->GetTokenSval().value();
	return sval_.compare("BOOLEAN") == 0;
}

void QueryLexer::MatchBooleanKeyword() {
	if (!HasBooleanKeyword()) throw SyntaxError(GenerateErrorMessage("BOOLEAN", tokenizer_->GetTokenSval().value_or("INTEGER")));
	this->tokenizer_->NextToken();
}


bool QueryLexer::HasMoreTokens() {
	return this->tokenizer_->GetToken().type_ != TokenType::kParseEnd;
}

bool QueryLexer::HasSuchThatKeywords() {
	return HasKeyword("such") && (PeekNextToken(1) == "that");
}

void QueryLexer::MatchSuchThatKeywords() {
	MatchKeyword("such");
	MatchKeyword("that");
}

bool QueryLexer::HasAttrName() {
	string sval = tokenizer_->GetTokenSval().value();
	for (string attr_name : attr_names_) {
		if (sval == attr_name) {
			return true;
		}
	}
	return false;
}

std::string QueryLexer::MatchAttrName() {
	if (!HasAttrName()) throw SyntaxError(GenerateErrorMessage("AttrName", tokenizer_->GetTokenSval().value_or("INTEGER")));
	string sval = tokenizer_->GetTokenSval().value();
	tokenizer_->NextToken();
	if (sval == "stmt") {
		MatchHashtag();
		sval += "#";
	}

	return sval;
}

string QueryLexer::GenerateErrorMessage(string expected, string actual) {
	return "Expected Token: " + expected + " ; Actual Token: " + actual;
};

std::string QueryLexer::PeekNextToken(int number_tokens_) {
	return this->tokenizer_->PeekNextToken(number_tokens_);
}

