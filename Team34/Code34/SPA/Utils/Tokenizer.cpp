#include "Tokenizer.h"

#include <cctype>
#include <string>
#include <optional>

#include "InvalidTokenException.h"

//Constructor: converts stack reference to string to pointer to char array in heap
Tokenizer::Tokenizer(const std::string& string) {
	int total_characters_in_query = string.length();
	this->query_pointer = new char[total_characters_in_query];
	this->current_index = -1;
	this->last_index = total_characters_in_query - 1;


	for (int index = 0; index < total_characters_in_query; index++) {
		this->query_pointer[index] = string[index];
	}
}

Tokenizer::~Tokenizer() {
	delete[] this->query_pointer;
}

TTYPE Tokenizer::getTokenType() {
	return this->current_token_type;
}

bool Tokenizer::hasNextToken() {
	return this->current_index < this->last_index;
}

std::optional<std::string> Tokenizer::getTokenSval() {
	return this->sval;
}

std::optional<int> Tokenizer::getTokenIval() {
	return this->ival;
}


void Tokenizer::nextToken() throw (InvalidTokenException) {
	if (this->current_index >= this->last_index) {
		consumeEndOfParsingToken();
		return;
	}
	this->current_index++;

	char current_char = this->query_pointer[current_index];
	if (isspace(current_char)) {
		consumeWhiteSpaceToken();
	}
	else if (isdigit(current_char)) {
		consumeIntegerToken();
	}
	else if (isalpha(current_char)) {
		consumeAlphanumericToken();

	}
	else if (current_char == ',') {
		consumeCommaToken();
	}
	else if (current_char == '<' || current_char == '>' || current_char == '=' || current_char == '!' || current_char == '+' || current_char == '-' || current_char == '/' || current_char == '*') {
		consumeOperatorToken();
	}
	else if (current_char == '(') {
		consumeClosingBracketToken();
	}
	else if (current_char == ')') {
		consumeOpeningBracketToken();
	}
	else {
		throw InvalidTokenException(current_char);
	}
}

void Tokenizer::consumeAlphanumericToken() {
	std::string tokenized_string = "";
	while (this->current_index < this->last_index && isalnum(this->query_pointer[current_index + 1])) {
		tokenized_string.push_back(this->query_pointer[current_index]);
		this->current_index++;
	}
	tokenized_string.push_back(this->query_pointer[current_index]);
	this->current_token_type = TTYPE::ALPHANUMERIC;
	this->sval = tokenized_string;
	this->ival = {};
}

void Tokenizer::consumeIntegerToken() {
	int val = this->query_pointer[current_index], power = 10;
	while (this->current_index < this->last_index && isdigit(this->query_pointer[current_index + 1])) {
		this->current_index++;
		val += power * (int)this->query_pointer[current_index];
		power *= 10;
	}
	this->current_token_type = TTYPE::INTEGER;
	this->sval = {};
	this->ival = val;

}

void Tokenizer::consumeWhiteSpaceToken() {

	while (this->current_index < this->last_index && isspace(this->query_pointer[current_index + 1])) {
		this->current_index++;
	}
	this->current_token_type = TTYPE::WHITESPACE;
	this->sval = {};
	this->ival = {};

}

void Tokenizer::consumeUnderScoreToken() {

	this->current_token_type = TTYPE::UNDERSCORE;
	this->sval = {};
	this->ival = {};

}

void Tokenizer::consumeCommaToken() {
	this->current_token_type = TTYPE::COMMA;
	this->sval = {};
	this->ival = {};
}

void Tokenizer::consumeOperatorToken() {

	std::string operator_token = "";
	operator_token.push_back(current_index);

	switch (this->query_pointer[this->current_index])
	{
	case '<': {}
	case '>': {}
	case '!': {}
	case '=':
	{
		if (this->current_index < this->last_index && this->query_pointer[this->current_index + 1] == '=') {
			this->current_index++;
			operator_token.push_back(this->current_index);
		}
		break;
	}
	default:
		break;
	}
	this->current_token_type = TTYPE::OPERATOR;
	this->sval = operator_token;
	this->ival = {};

}

void Tokenizer::consumeOpeningBracketToken() {
	this->current_token_type = TTYPE::OPENING_BRACKET;
	this->sval = "(";
	this->ival = {};


}

void Tokenizer::consumeClosingBracketToken() {
	this->current_token_type = TTYPE::OPENING_BRACKET;
	this->sval = ")";
	this->ival = {};
}

void Tokenizer::consumeEndOfParsingToken() {
	this->current_token_type = TTYPE::END_OF_PARSING;
	this->ival = {};
	this->sval = {};
}


