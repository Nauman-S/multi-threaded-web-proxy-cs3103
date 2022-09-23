#pragma once

#include <string>
#include <regex>
#include <map>

enum TokenType {
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


    // Self-defined for parsing usage
    kParseStart,
    kParseEnd,
};

class Token {
private:
    const static std::regex name_regex_;
    const static std::regex integer_regex_;
    const static std::map<char, TokenType> allowed_special_char_;
public:
    std::string literal_value_;
    TokenType type_;

    Token(std::string, TokenType);

    static bool IsName(std::string);
    static bool IsInteger(std::string);
    static bool IsValidToken(char);
    static TokenType GetTokenTypeByChar(char);
};

