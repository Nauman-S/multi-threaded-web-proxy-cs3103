#include "SourceToken.h"

SourceToken::SourceToken(SourceTokenType type, std::string val) : type_(type), str_val_(val) {}

SourceTokenType SourceToken::GetType() {
    return this->type_;
}

std::string SourceToken::GetStringVal() {
    return this->str_val_;
}

