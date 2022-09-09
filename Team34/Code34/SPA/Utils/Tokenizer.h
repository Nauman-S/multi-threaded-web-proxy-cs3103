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

	void consumeAlphanumericToken(int* current_index_);
	void consumeIntegerToken(int* current_index_);
	void consumeEndOfParsingToken();
	void consumeSpecialCharacter();
	void skipIgnoredChars(int* current_index_);
	bool isIgnoredChar(char);
public:
	~Tokenizer();

	void feedLine(const std::string& string);
	void nextToken();
	void MoveToNextToken(int* current_index_);
	bool hasNextToken();
	Token PeekNextToken(int number_tokens_);

	Token getToken();

	std::optional<std::string> getTokenSval();

	std::optional<int> Tokenizer::getTokenIval();
};

#endif

