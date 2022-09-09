#include "Tokenizer.h"

#include <cctype>
#include <string>
#include <optional>

#include "InvalidTokenException.h"
#include "Token.h"

Tokenizer::~Tokenizer() {
	delete[] this->query_pointer;
}

//converts stack reference to string to pointer to char array in heap
void Tokenizer::feedLine(const std::string& string) {
	delete[] this->query_pointer;
	int total_characters_in_query = string.length();
	this->query_pointer = new char[total_characters_in_query];
	this->current_index = -1;
	this->last_index = total_characters_in_query - 1;


	for (int index = 0; index < total_characters_in_query; index++) {
		this->query_pointer[index] = string[index];
	}
}

Token Tokenizer::getToken() {
	return this->current_token;
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


void Tokenizer::nextToken() {
	skipIgnoredChars();
	if (this->current_index >= this->last_index) {
		consumeEndOfParsingToken();
		return;
	}
	this->current_index++;

	char current_char = this->query_pointer[current_index];
	if (isdigit(current_char)) {
		consumeIntegerToken();
	}
	else if (isalpha(current_char)) {
		consumeAlphanumericToken();

	}
	else if (Token::IsValidToken(current_char)) {
		consumeSpecialCharacter();
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
	this->current_token = Token(tokenized_string, TokenType::kName);
	this->sval = tokenized_string;
	this->ival = {};
}

void Tokenizer::consumeIntegerToken() {
	std::string int_string = "";
	int val = this->query_pointer[current_index], power = 10;
	int_string.push_back(this->query_pointer[current_index]);
	while (this->current_index < this->last_index && isdigit(this->query_pointer[current_index + 1])) {
		this->current_index++;
		val += power * (int)this->query_pointer[current_index];
		power *= 10;
		int_string.push_back(this->query_pointer[current_index]);
	}
	this->current_token = Token(int_string, TokenType::kInteger);
	this->sval = {};
	this->ival = val;

}

void Tokenizer::skipIgnoredChars() {

	while (this->current_index < this->last_index && isIgnoredChar(this->query_pointer[current_index + 1])) {
		this->current_index++;
	}

}

void Tokenizer::consumeSpecialCharacter() {

	char current_char = this->query_pointer[current_index];
	TokenType type = Token::GetTokenTypeByChar(current_char);

	this->current_token = Token(std::string(1, current_char), type);
	this->sval = {};
	this->ival = {};

}

void Tokenizer::consumeEndOfParsingToken() {
	this->current_token = Token("", TokenType::kParseEnd);
	this->ival = {};
	this->sval = {};
}

bool Tokenizer::isIgnoredChar(char c) {
	// Only ignore spaces and line breaks
	return isspace(c) || c == '\n';
}

