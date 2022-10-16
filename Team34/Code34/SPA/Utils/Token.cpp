#include "Token.h"

#include <map>

using namespace std;

// Complete map of all possible allowed special characters besides LETTER and DIGIT
const map<char, TokenType> Token::allowed_special_char_{
    // Operators, or part of an operator
    {'=', TokenType::kEqual},
    {'!', TokenType::kNegate},
    {'&', TokenType::kAmpersand},
    {'|', TokenType::kPipe},
    {'>', TokenType::kGreater},
    {'<', TokenType::kLesser},
    {'+', TokenType::kAdd},
    {'-', TokenType::kMinus},
    {'*', TokenType::kMultiply},
    {'/', TokenType::kkDivide},
    {'%', TokenType::kModulo},

    // Structural delimiters
    {'(', TokenType::kLeftRound},
    {')', TokenType::kRightRound},
    {'{', TokenType::kLeftCurly},
    {'}', TokenType::kRightCurly},
    {';', TokenType::kSemiColon},
    {',', TokenType::kComma},
    {'_', TokenType::kUnderscore},
    {'\"', TokenType::kDoubleQuote},
    {'\'', TokenType::kSingleQuote},
    {'.', TokenType::kFullStop},
    {'#', TokenType::kHashtag}
};

Token::Token(std::string value, TokenType type) : literal_value_(value), type_(type) {}

std::string& Token::GetStringValue() { 
    return this->literal_value_; 
}

TokenType Token::GetType() { 
    return this->type_; 
}

bool Token::IsValidToken(char c) {
    return Token::allowed_special_char_.find(c) != Token::allowed_special_char_.end();
}

// Returns TokenType assuming char key exists in map
TokenType Token::GetTokenTypeByChar(char c) {
    return Token::allowed_special_char_.at(c);
}

