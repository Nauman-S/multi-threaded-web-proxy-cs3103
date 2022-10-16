#pragma once

#include <string>

enum class SourceTokenType {
    // Basic unit of name identifier and digits
    kName,
    kInteger,

    // Operators
    kEqual,
    kDoubleEqual,
    kNegate,
    kNotEqual,
    kLogicalAnd,
    kLogicalOr,
    kGreater,
    kGreaterEqual,
    kLesser,
    kLesserEqual,
    kAdd,
    kMinus,
    kMultiply,
    kDivide,
    kModulo,

    // Structural delimiters
    kLeftRound,
    kRightRound,
    kLeftCurly,
    kRightCurly,
    kSemiColon,
};

class SourceToken {
public:
    SourceToken(SourceTokenType, std::string);

    SourceTokenType GetType();
    std::string GetStringVal();

    // Keyword matchers
    bool IsProcedure();
    bool IsRead();
    bool IsPrint();
    bool IsCall();
    bool IsWhile();
    bool IsIf();
    bool IsThen();
    bool IsElse();

    bool operator==(const SourceToken&);

private:
    SourceTokenType type_;
    std::string str_val_;
};

