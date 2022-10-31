#pragma once

#include <string>
#include <optional>

#include "InvalidTokenException.h"
#include "Token.h"

class Tokenizer
{
public:
    ~Tokenizer();

    void FeedLine(const std::string& string);
    bool HasNextToken();
    void NextToken();
    std::string PeekNextToken(int number_tokens_);

    Token GetToken();
    std::optional<std::string> GetTokenSval();
    std::optional<int> Tokenizer::GetTokenIval();

private:
    std::optional<int> ival = {};
    std::optional<std::string> sval = {};

    char* query_pointer = NULL;
    int current_index = 0;
    int last_index = 0;

    Token current_token = Token("", TokenType::kParseStart);

    void MoveToNextToken(int* current_index_);
    void ConsumeAlphanumericToken(int* current_index_);
    void ConsumeIntegerToken(int* current_index_);
    void ConsumeEndOfParsingToken();
    void ConsumeSpecialCharacter();
    void SkipIgnoredChars(int* current_index_);
    bool IsIgnoredChar(char);
};
