#pragma once
#include <string>
#include <optional>

#include "InvalidTokenException.h"
#include "Token.h"

#ifndef TOKENIZER
#define TOKENIZER

class Tokenizer
{
private:

	std::optional<int> ival = {};
	std::optional<std::string> sval = {};

	char* query_pointer = NULL;
	int current_index;
	int last_index;

	Token current_token = Token("", TokenType::kParseStart);

	void ConsumeAlphanumericToken(int* current_index_);
	void ConsumeIntegerToken(int* current_index_);
	void ConsumeEndOfParsingToken();
	void ConsumeSpecialCharacter();
	void SkipIgnoredChars(int* current_index_);
	bool IsIgnoredChar(char);
public:
	~Tokenizer();

	void FeedLine(const std::string& string);
	void NextToken();
	void MoveToNextToken(int* current_index_);
	bool HasNextToken();
	std::string PeekNextToken(int number_tokens_);

	Token GetToken();

	std::optional<std::string> GetTokenSval();

	std::optional<int> Tokenizer::GetTokenIval();
};

#endif

