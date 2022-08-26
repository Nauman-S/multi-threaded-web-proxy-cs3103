#pragma once
#include <string>
#include <optional>

#include "InvalidTokenException.h"

#ifndef TOKENIZER
#define TOKENIZER
enum class TTYPE { PRE_PARSING, ALPHANUMERIC, INTEGER, WHITESPACE, UNDERSCORE, COMMA, OPERATOR, OPENING_BRACKET, CLOSING_BRACKET, END_OF_PARSING };

class Tokenizer
{
private:

	std::optional<int> ival = {};
	std::optional<std::string> sval = {};

	char* query_pointer;
	int current_index;
	int last_index;

	TTYPE current_token_type = TTYPE::PRE_PARSING;

	void consumeAlphanumericToken();
	void consumeIntegerToken();
	void consumeWhiteSpaceToken();
	void consumeUnderScoreToken();
	void consumeCommaToken();
	void consumeOperatorToken();
	void consumeOpeningBracketToken();
	void consumeClosingBracketToken();
	void consumeEndOfParsingToken();
public:
	Tokenizer(const std::string& string);
	~Tokenizer();

	void nextToken();

	bool Tokenizer::hasNextToken();

	TTYPE getTokenType();

	std::optional<std::string> getTokenSval();

	std::optional<int> Tokenizer::getTokenIval();
};

#endif

