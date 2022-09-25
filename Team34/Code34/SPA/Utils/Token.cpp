#include "Token.h"

#include <regex>
#include <map>

using namespace std;

// SIMPLE grammar rules:
// - LETTER: 'A'-'Z' | 'a'-'z'
// - DIGIT: 0-9
// - NAME: LETTER (LETTER | DIGIT)*
// - INTEGER: DIGIT+
const regex Token::name_regex_ = regex("[a-zA-Z][a-zA-Z0-9]*");
const regex Token::integer_regex_ = regex("\\d+");

// Complete map of all possible allowed special characters besides LETTER and DIGIT
const map<char, TokenType> Token::allowed_special_char_{
    // Operators, or part of an operator
    {'=', kEqual},
    {'!', kNegate},
    {'&', kAmpersand},
    {'|', kPipe},
    {'>', kGreater},
    {'<', kLesser},
    {'+', kAdd},
    {'-', kMinus},
    {'*', kMultiply},
    {'/', kkDivide},
    {'%', kModulo},

    // Structural delimiters
    {'(', kLeftRound},
    {')', kRightRound},
    {'{', kLeftCurly},
    {'}', kRightCurly},
    {';', kSemiColon},
    {',', kComma},
    {'_', kUnderscore},
    {'\"', kDoubleQuote},
    {'\'', kSingleQuote},
    {'.', kFullStop},
    //{'#', kHashtag},
};

Token::Token(std::string value, TokenType type) : literal_value_(value), type_(type) {}

bool Token::IsName(string token_string) {
    return regex_match(token_string, Token::name_regex_);
}

bool Token::IsInteger(std::string token_string) {
    return regex_match(token_string, Token::integer_regex_);
}

bool Token::IsValidToken(char c) {
    return Token::allowed_special_char_.find(c) != Token::allowed_special_char_.end();
}

// Returns TokenType assuming char key exists in map
TokenType Token::GetTokenTypeByChar(char c) {
    return Token::allowed_special_char_.at(c);
}

