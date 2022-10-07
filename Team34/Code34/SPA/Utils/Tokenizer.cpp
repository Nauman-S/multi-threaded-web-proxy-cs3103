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
void Tokenizer::FeedLine(const std::string& string) {
	delete[] this->query_pointer;
	int total_characters_in_query = string.length();
	this->query_pointer = new char[total_characters_in_query];
	this->current_index = -1;
	this->last_index = total_characters_in_query - 1;


	for (int index = 0; index < total_characters_in_query; index++) {
		this->query_pointer[index] = string[index];
	}
}

Token Tokenizer::GetToken() {
	return this->current_token;
}

bool Tokenizer::HasNextToken() {
	this->SkipIgnoredChars(&this->current_index);
	return this->current_index < this->last_index;
}

std::optional<std::string> Tokenizer::GetTokenSval() {
	return this->sval;
}

std::optional<int> Tokenizer::GetTokenIval() {
	return this->ival;
}


std::string Tokenizer::PeekNextToken(int number_tokens_) {
	Token current_token_store_ = this->current_token;
	std::optional<int> current_ival_store_ = this->ival;
	std::optional<std::string> current_sval_store_ = this->sval;
	int current_index_copy_ = this->current_index;
	for (int i = 0; i < number_tokens_; i++) {
		MoveToNextToken(&current_index_copy_);
	}
	std::string peeked_token_ = this->GetTokenSval().value_or("");
	this->current_token = current_token_store_;
	this->ival = current_ival_store_;
	this->sval = current_sval_store_;
	return peeked_token_;
}

void Tokenizer::MoveToNextToken(int* current_index_) {

	SkipIgnoredChars(current_index_);
	if (*current_index_ >= this->last_index) {
		ConsumeEndOfParsingToken();
		return;
	}
	(*current_index_)++;

	char current_char = this->query_pointer[*current_index_];
	if (isdigit(current_char)) {
		ConsumeIntegerToken(current_index_);
	}
	else if (isalpha(current_char)) {
		ConsumeAlphanumericToken(current_index_);

	}
	else if (Token::IsValidToken(current_char)) {
		ConsumeSpecialCharacter();
	}
	else {
		throw InvalidTokenException(current_char);
	}
}

void Tokenizer::NextToken() {
	MoveToNextToken(&this->current_index);
}

void Tokenizer::ConsumeAlphanumericToken(int* current_index_) {
	std::string tokenized_string = "";
	while (*current_index_ < this->last_index && isalnum(this->query_pointer[*current_index_ + 1])) {
		tokenized_string.push_back(this->query_pointer[*current_index_]);
		(*current_index_)++;
	}
	tokenized_string.push_back(this->query_pointer[*current_index_]);
	this->current_token = Token(tokenized_string, TokenType::kName);
	this->sval = tokenized_string;
	this->ival = {};
}

void Tokenizer::ConsumeIntegerToken(int* current_index_) {
	std::string int_string = "";
	int_string.push_back(this->query_pointer[*current_index_]);
	while (*current_index_ < this->last_index && isdigit(this->query_pointer[*current_index_ + 1])) {
		(*current_index_)++;
		int_string.push_back(this->query_pointer[*current_index_]);
	}
	this->current_token = Token(int_string, TokenType::kInteger);
	this->sval = {};
	this->ival = stoi(int_string);

}

void Tokenizer::SkipIgnoredChars(int* current_index_) {

	while (*current_index_ < this->last_index && IsIgnoredChar(this->query_pointer[*current_index_ + 1])) {
		(*current_index_)++;
	}

}

void Tokenizer::ConsumeSpecialCharacter() {

	char current_char = this->query_pointer[current_index];
	TokenType type = Token::GetTokenTypeByChar(current_char);

	this->current_token = Token(std::string(1, current_char), type);
	this->sval = {};
	this->ival = {};

}

void Tokenizer::ConsumeEndOfParsingToken() {
	this->current_token = Token("", TokenType::kParseEnd);
	this->ival = {};
	this->sval = {};
}

bool Tokenizer::IsIgnoredChar(char c) {
	// Only ignore spaces and line breaks
	return isspace(c) || c == '\n';
}

