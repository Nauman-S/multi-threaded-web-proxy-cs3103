#include "QueryLexer.h"
#include <algorithm>

#include "../reference/EntityRef.h"
#include "StringLiterals.h"

using namespace StringLiterals;

void QueryLexer::InitializeKeywords() {
    relation_keywords_.insert({ FOLLOWS, FOLLOWST, PARENT, PARENTT, USES, MODIFIES,
        NEXT, NEXTT, CALLS, CALLST, AFFECTS, AFFECTST });
    design_entities_.insert({ EntityRef::kStmt, EntityRef::kRead, EntityRef::kPrint, EntityRef::kCall, EntityRef::kWhile,
        EntityRef::kIf, EntityRef::kAssign, EntityRef::kVariable, EntityRef::kConstant, EntityRef::kProcedure });
    attr_names_.insert({ PROC_NAME, VAR_NAME, VALUE, STMT });
    operators_.insert({ TokenType::kAdd, TokenType::kMinus, TokenType::kkDivide, TokenType::kMultiply,TokenType::kModulo });
}

QueryLexer::QueryLexer() {
    InitializeKeywords();
    this->tokenizer_ = std::make_shared<Tokenizer>();
}

void QueryLexer::FeedQuery(const std::string& query_string) {
    this->tokenizer_->FeedLine(query_string);
    this->tokenizer_->NextToken();
}

bool QueryLexer::HasDesignEntity() {
    if (IsCurrentTokenOfType(TokenType::kName)) {
        std::string sval_ = this->tokenizer_->GetTokenSval().value();
        if (this->design_entities_.find(sval_) != this->design_entities_.end()) {
            return true;
        }
    }
    return false;
}

std::string QueryLexer::MatchDesignEntityKeyword() {
    if (!HasDesignEntity()) throw SyntaxError(GenerateErrorMessage("design entity keyword"));
    std::string sval_ = this->tokenizer_->GetTokenSval().value();
    this->tokenizer_->NextToken();
    return sval_;
}

bool QueryLexer::HasIdentity() {
    return IsCurrentTokenOfType(TokenType::kName);
}

std::string QueryLexer::MatchIdentity() {
    if (!HasIdentity()) throw SyntaxError(GenerateErrorMessage("IDENTITY"));
    std::string sval_ = this->tokenizer_->GetTokenSval().value();
    this->tokenizer_->NextToken();
    return sval_;
}

bool QueryLexer::HasEndOfDeclarationStatement() {
    return IsCurrentTokenOfType(TokenType::kSemiColon);
}

void QueryLexer::MatchEndOfDeclarationStatement() {
    if (!HasEndOfDeclarationStatement()) throw SyntaxError(GenerateErrorMessage(SEMICOLON));
    this->tokenizer_->NextToken();
}

bool QueryLexer::HasKeyword(std::string keyword) {
    if (IsCurrentTokenOfType(TokenType::kName)) {
        std::string sval_ = this->tokenizer_->GetTokenSval().value();
        return sval_.compare(keyword) == 0;
    }
    return false;
}

void QueryLexer::MatchKeyword(std::string keyword) {
    if (!HasKeyword(keyword)) throw SyntaxError();
    tokenizer_->NextToken();
}

bool QueryLexer::HasSelectKeyword() {
    return HasKeyword(SELECT);
}

void QueryLexer::MatchSelectKeyword() {
    if (!HasSelectKeyword()) throw SyntaxError(GenerateErrorMessage(SELECT));
    this->tokenizer_->NextToken();
}

bool QueryLexer::HasReferenceKeyword() {
    if (IsCurrentTokenOfType(TokenType::kName)) {
        std::string sval_ = this->tokenizer_->GetTokenSval().value();
        if (this->relation_keywords_.find(sval_) != this->relation_keywords_.end()) {
            return true;
        }
    }
    return false;
}

std::string QueryLexer::MatchReferenceKeyword() {
    if (!HasReferenceKeyword()) throw SyntaxError();
    std::string sval_ = this->tokenizer_->GetTokenSval().value();
    this->tokenizer_->NextToken();
    if (IsCurrentTokenOfType(TokenType::kMultiply)) {
        sval_ += MULTIPLE;
        this->tokenizer_->NextToken();
    }
    return sval_;
}

bool QueryLexer::HasLeftBrace() {
    return IsCurrentTokenOfType(TokenType::kLeftRound);
}

void QueryLexer::MatchLeftBrace() {
    if (!HasLeftBrace()) throw SyntaxError(GenerateErrorMessage(LEFT_BRACE));
    tokenizer_->NextToken();
}

bool QueryLexer::HasRightBrace() {
    return IsCurrentTokenOfType(TokenType::kRightRound);
}

void QueryLexer::MatchRightBrace() {
    if (!HasRightBrace()) throw SyntaxError(GenerateErrorMessage(RIGHT_BRACE));
    tokenizer_->NextToken();
}

bool QueryLexer::HasLeftAngle() {
    return IsCurrentTokenOfType(TokenType::kLesser);
}

void QueryLexer::MatchLeftAngle() {
    if (!HasLeftAngle()) throw SyntaxError(GenerateErrorMessage(LEFT_ANGLE));
    tokenizer_->NextToken();
}

bool QueryLexer::HasRightAngle() {
    return IsCurrentTokenOfType(TokenType::kGreater);
}

void QueryLexer::MatchRightAngle() {
    if (!HasRightAngle()) throw SyntaxError(GenerateErrorMessage(RIGHT_ANGLE));
    tokenizer_->NextToken();
}

bool QueryLexer::HasUnderScore() {
    return IsCurrentTokenOfType(TokenType::kUnderscore);
}

void QueryLexer::MatchUnderScore() {
    if (!HasUnderScore()) throw SyntaxError(GenerateErrorMessage(UNDERSCORE));
    tokenizer_->NextToken();
}

bool QueryLexer::HasFullStop() {
    return IsCurrentTokenOfType(TokenType::kFullStop);
}

void QueryLexer::MatchFullStop() {
    if (!HasFullStop()) throw SyntaxError(GenerateErrorMessage(FULLSTOP));
    tokenizer_->NextToken();
}

bool QueryLexer::HasEqualSign() {
    return IsCurrentTokenOfType(TokenType::kEqual);
}

void QueryLexer::MatchEqualSign() {
    if (!HasEqualSign()) throw SyntaxError(GenerateErrorMessage(EQUAL));
    tokenizer_->NextToken();
}

bool QueryLexer::HasQuotationMarks() {
    return IsCurrentTokenOfType(TokenType::kDoubleQuote) || IsCurrentTokenOfType(TokenType::kSingleQuote);
}

void QueryLexer::MatchQuotationMarks() {
    if (!HasQuotationMarks()) throw SyntaxError(GenerateErrorMessage(QUATATION));
    this->tokenizer_->NextToken();
}

bool QueryLexer::HasComma() {
    return IsCurrentTokenOfType(TokenType::kComma);
}

void QueryLexer::MatchComma() {
    if (!HasComma()) throw SyntaxError(GenerateErrorMessage(COMMA));
    tokenizer_->NextToken();
}

bool QueryLexer::HasHashtag() {
    return IsCurrentTokenOfType(TokenType::kHashtag);
}

void QueryLexer::MatchHashtag() {
    if (!HasHashtag()) throw SyntaxError(GenerateErrorMessage(HASHTAG));
    tokenizer_->NextToken();
}

bool QueryLexer::HasInteger() {
    return IsCurrentTokenOfType(TokenType::kInteger);
}

bool QueryLexer::HasOperator() {
    Token& token = this->tokenizer_->GetToken();
    return this->operators_.find(token.GetType()) != this->operators_.end();
}

std::string QueryLexer::MatchOperator() {
    std::string operator_string_;
    Token& token = this->tokenizer_->GetToken();
    if (token.GetType() == TokenType::kAdd) {
        operator_string_ = PLUS;
    } else if (token.GetType() == TokenType::kMinus) {
        operator_string_ = MINUS;
    } else if (token.GetType() == TokenType::kkDivide) {
        operator_string_ = DIVIDE;
    } else if (token.GetType() == TokenType::kMultiply) {
        operator_string_ = MULTIPLE;
    } else if (token.GetType() == TokenType::kModulo) {
        operator_string_ = MODULO;
    }
    this->tokenizer_->NextToken();
    return operator_string_;
}

int QueryLexer::MatchInteger() {
    if (!HasInteger()) throw SyntaxError();
    int i = this->tokenizer_->GetTokenIval().value();
    this->tokenizer_->NextToken();
    return i;
}

bool QueryLexer::HasClauseKeyword() {
    return HasPatternKeyword() || HasSuchThatKeywords() || HasWithKeyword();
}

bool QueryLexer::HasPatternKeyword() {
    return HasKeyword(PATTERN);
}

void QueryLexer::MatchPatternKeyword() {
    if (!HasPatternKeyword()) throw SyntaxError(GenerateErrorMessage(PATTERN));
    tokenizer_->NextToken();
}

bool QueryLexer::HasWithKeyword() {
    return HasKeyword(WITH);
}

void QueryLexer::MatchWithKeyword() {
    if (!HasWithKeyword()) throw SyntaxError(GenerateErrorMessage(WITH));
    tokenizer_->NextToken();
}

bool QueryLexer::HasAndKeyword() {
    return HasKeyword(AND);
}

void QueryLexer::MatchAndKeyword() {
    if (!HasAndKeyword()) throw SyntaxError(GenerateErrorMessage(AND));
    tokenizer_->NextToken();
}

bool QueryLexer::HasBooleanKeyword() {
    return HasKeyword(BOOLEAN);
}

void QueryLexer::MatchBooleanKeyword() {
    if (!HasBooleanKeyword()) throw SyntaxError(GenerateErrorMessage(BOOLEAN));
    tokenizer_->NextToken();
}

bool QueryLexer::HasMoreTokens() {
    return !IsCurrentTokenOfType(TokenType::kParseEnd);
}

bool QueryLexer::HasSuchThatKeywords() {
    return HasKeyword(SUCH) && (PeekNextToken(1) == THAT);
}

void QueryLexer::MatchSuchThatKeywords() {
    MatchKeyword(SUCH);
    MatchKeyword(THAT);
}

bool QueryLexer::HasAttrName() {
    string sval = tokenizer_->GetTokenSval().value();
    for (string attr_name : attr_names_) {
        if (sval == attr_name) {
            return true;
        }
    }
    return false;
}

std::string QueryLexer::MatchAttrName() {
    if (!HasAttrName()) throw SyntaxError();
    string sval = tokenizer_->GetTokenSval().value();
    tokenizer_->NextToken();
    if (sval == STMT) {
        MatchHashtag();
        sval += HASHTAG;
    }
    return sval;
}

string QueryLexer::GenerateErrorMessage(string expected) {
    return "Expected Token: " + expected + " ; Actual Token: " + tokenizer_->GetTokenSval().value_or("INTEGER");
}

std::string QueryLexer::PeekNextToken(int number_tokens_) {
    return this->tokenizer_->PeekNextToken(number_tokens_);
}

bool QueryLexer::IsCurrentTokenOfType(TokenType type) {
    Token& token = this->tokenizer_->GetToken();
    return token.GetType() == type;
}
