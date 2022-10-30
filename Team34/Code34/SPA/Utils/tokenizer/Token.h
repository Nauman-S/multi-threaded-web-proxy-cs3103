#pragma once

#include <string>
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
private:
    static const std::map<char, TokenType> allowed_special_char_;

    std::string literal_value_;
    TokenType type_;

public:
    Token(std::string, TokenType);
    std::string& GetStringValue();
    TokenType GetType();

    static bool IsValidToken(char);
    static TokenType GetTokenTypeByChar(char);
};

