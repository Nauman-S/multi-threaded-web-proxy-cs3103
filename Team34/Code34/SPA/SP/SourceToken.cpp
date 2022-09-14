#include "SourceToken.h"

SourceToken::SourceToken(SourceTokenType type, std::string val) : type_(type), str_val_(val) {}

SourceTokenType SourceToken::GetType() {
    return this->type_;
}

std::string SourceToken::GetStringVal() {
    return this->str_val_;
}

bool SourceToken::IsProcedure() {
    return this->str_val_ == "procedure";
}
bool SourceToken::IsRead() {
    return this->str_val_ == "read";
}
bool SourceToken::IsPrint() {
    return this->str_val_ == "print";
}
bool SourceToken::IsCall() {
    return this->str_val_ == "call";
}
bool SourceToken::IsWhile() {
    return this->str_val_ == "while";
}
bool SourceToken::IsIf() {
    return this->str_val_ == "if";
}
bool SourceToken::IsThen() {
    return this->str_val_ == "then";
}
bool SourceToken::IsElse() {
    return this->str_val_ == "else";
}
