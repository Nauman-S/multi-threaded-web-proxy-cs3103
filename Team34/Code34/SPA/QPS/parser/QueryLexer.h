#pragma once
#include <string>
#include <unordered_set>
#include "..\..\Utils\Tokenizer.h"
#include "..\..\Utils\Token.h"


#ifndef QUERYLEXER_H
#define QUERYLEXER_H
class QueryLexer
{
private:

	Tokenizer* tokenizer_;
	std::unordered_set<std::string> design_entities_;
	std::unordered_set<std::string> relation_keywords_;
	std::unordered_set<std::string> keywords_;
	std::unordered_set <char> delimiters_;

	void InitializeKeywords();

public:

	QueryLexer();
	~QueryLexer();
	void FeedQuery(const std::string& query_string_);

	bool HasDesignEntity();
	std::string MatchDesignEntityKeyword();

	bool HasIdentity();
	std::string MatchIdentity();

	bool HasEndOfDeclarationStatement();
	std::string MatchEndOfDeclarationStatement();

	bool HasKeyword(std::string keyword_);
	void MatchKeyword();


	bool HasReferenceKeyword();
	std::string MatchReferenceKeyword();


	bool HasOpeningBrace();
	std::string MatchOpeningBrace();

	bool HasClosingBrace();
	std::string MatchClosingBrace();

	bool HasCommaDelimeter();
	std::string MatchCommaDelimeter();

	bool HasInteger();
	int MatchInteger();

	bool HasUnderScore();
	void MatchUnderScore();

	bool HasPatternKeyword();
	std::string MatchPatternKeyword();

	bool HasMoreTokens();

	bool HasQuotationMarks();
	void MatchQuotationMarks();


};
#endif


