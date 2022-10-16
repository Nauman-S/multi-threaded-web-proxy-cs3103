#pragma once

#include <string>
#include <regex>
#include <map>

enum class TokenType {
    // Basic unit of name identifier and digits
    kName,
    kInteger,

    // Operators, or part of an operator
    kEqual,
    kNegate,
    kAmpersand,
    kPipe,
    kGreater,
    kLesser,
    kAdd,
    kMinus,
    kMultiply,
    kkDivide,
    kModulo,

    // Structural delimiters
    kLeftRound,
    kRightRound,
    kLeftCurly,
    kRightCurly,
    kSemiColon,
    kComma,
    kUnderscore,
    kSingleQuote,
    kDoubleQuote,
    kFullStop,
    kHashtag,

    // Self-defined for parsing usage
    kParseStart,
    kParseEnd,
};

class Token {
public:
    std::string literal_value_;
    TokenType type_;

    Token(std::string, TokenType);
    std::string& GetStringValue();
    TokenType GetType();

    static bool IsValidToken(char);
    static TokenType GetTokenTypeByChar(char);

private:
    const static std::map<char, TokenType> allowed_special_char_;
};

