#include "SourceLexer.h"

#include <iostream>

#include "..\..\Utils\Token.h"
#include "..\..\Utils\InvalidTokenException.h"
#include "SourceToken.h"

using namespace std;

SourceLexer::SourceLexer(const string& source_filename) {
    this->file_stream_.open(source_filename);
    string s;
    if (getline(this->file_stream_, s)) {
        this->tokenizer_.FeedLine(s);
    }
}

std::shared_ptr<vector<SourceToken>> SourceLexer::GetAllTokens() {
    std::shared_ptr<vector<SourceToken>> results(new vector<SourceToken>);
    while (HasNextToken()) {
        SourceToken token = ConstructSourceToken();
        results->push_back(token);
    }
    return results;
}

const std::map<std::string, SourceTokenType> SourceLexer::keywords_ = {
    {"procedure", SourceTokenType::kProcedure},
    {"read", SourceTokenType::kRead},
    {"print", SourceTokenType::kPrint},
    {"call", SourceTokenType::kCall},
    {"while", SourceTokenType::kWhile},
    {"if", SourceTokenType::kIf},
    {"then", SourceTokenType::kThen},
    {"else", SourceTokenType::kElse},
};

const std::map<std::string, SourceTokenType> SourceLexer::allowed_tokens_ = {
    // Operators
    {"=", SourceTokenType::kEqual},
    {"==", SourceTokenType::kDoubleEqual},
    {"!", SourceTokenType::kNegate},
    {"!=", SourceTokenType::kNotEqual},
    {"&&", SourceTokenType::kLogicalAnd},
    {"||", SourceTokenType::kLogicalOr},
    {">", SourceTokenType::kGreater},
    {">=", SourceTokenType::kGreaterEqual},
    {"<", SourceTokenType::kLesser},
    {"<=", SourceTokenType::kLesserEqual},
    {"+", SourceTokenType::kAdd},
    {"-", SourceTokenType::kMinus},
    {"*", SourceTokenType::kMultiply},
    {"/", SourceTokenType::kDivide},
    {"%", SourceTokenType::kModulo},

    // Structural delimiters
    {"(", SourceTokenType::kLeftRound},
    {")", SourceTokenType::kRightRound},
    {"{", SourceTokenType::kLeftCurly},
    {"}", SourceTokenType::kRightCurly},
    {";", SourceTokenType::kSemiColon},
};

// Set of characters that is part of a possible multi character token
// For example, & in &&, | in ||, > in >=, etc...
const std::set<string> SourceLexer::multi_char_tokens_starter_ = {
    "&", "|", ">", "<", "=", "!"
};

SourceToken SourceLexer::ConstructSourceToken() {
    Token token = GetNextToken();
    if (IsMultiTokenStarter(token)) {
        token = CombineMultiToken(token);
    }

    SourceTokenType type;
    if (token.GetType() == TokenType::kName) {
        type = SourceTokenType::kName;
    }
    else if (token.GetType() == TokenType::kInteger) {
        type = SourceTokenType::kInteger;
    }
    else if (IsValidToken(token.GetStringValue())) {
        type = GetValidTokenType(token.GetStringValue());
    }
    else {
        throw InvalidTokenException(token.GetStringValue());
    }

    return SourceToken(type, token.GetStringValue());
};

bool SourceLexer::HasNextToken() {
    if (!this->buffer_.empty() || this->tokenizer_.HasNextToken()) {
        return true;
    }

    string line;
    while (getline(this->file_stream_, line)) {
        this->tokenizer_.FeedLine(line);
        if (this->tokenizer_.HasNextToken()) {
            return true;
        };
    }

    // Finished consumption of both tokenizer stream and file stream
    return false;
}

Token SourceLexer::GetNextToken() {
    if (!this->buffer_.empty()) {
        // Use remaining tokens from buffer first
        Token token = this->buffer_[0];
        this->buffer_.erase(this->buffer_.begin());
        return token;
    }

    this->tokenizer_.NextToken();
    return this->tokenizer_.GetToken();
}

// Do a lookahead for the next token and attempt to combine
// the given token with the next, if the combination results in
// a valid token. We will always choose the token that consumes
// a greater number of characters (maximal-munch)
Token SourceLexer::CombineMultiToken(Token& token) {
    if (!HasNextToken()) {
        return token;
    }

    Token followed_token = GetNextToken();
    string combined_literal = token.GetStringValue() + followed_token.GetStringValue();
    if (IsValidToken(combined_literal)) {
        return Token(combined_literal, TokenType::kParseStart);
    }
    else {
        // Tokens cannot be combined, store it for consumption in next operation
        this->buffer_.push_back(followed_token);
        return token;
    }
}

bool SourceLexer::IsMultiTokenStarter(Token& token) {
    return multi_char_tokens_starter_.find(token.GetStringValue()) != multi_char_tokens_starter_.end();
}

bool SourceLexer::IsKeyword(Token& token) {
    bool is_identifier = token.GetType() == TokenType::kName;
    bool matches_keyword = keywords_.find(token.GetStringValue()) != keywords_.end();
    return is_identifier && matches_keyword;
}

bool SourceLexer::IsValidToken(const string& literal_value) {
    return allowed_tokens_.find(literal_value) != allowed_tokens_.end();
}

SourceTokenType SourceLexer::GetKeywordType(const string& literal_value) {
    return keywords_.at(literal_value);
}
SourceTokenType SourceLexer::GetValidTokenType(const string& literal_value) {
    return allowed_tokens_.at(literal_value);
}

