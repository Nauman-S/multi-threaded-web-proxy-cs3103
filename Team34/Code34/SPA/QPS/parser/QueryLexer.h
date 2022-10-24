#pragma once

#include <string>
#include <unordered_set>
#include <memory>

#include "..\..\Utils\tokenizer\Tokenizer.h"
#include "..\..\Utils\tokenizer\Token.h"

using std::string;

#ifndef QUERYLEXER_H
#define QUERYLEXER_H
class QueryLexer {
private:
    std::shared_ptr<Tokenizer> tokenizer_;
    std::unordered_set<std::string> design_entities_;
    std::unordered_set<std::string> relation_keywords_;
    std::unordered_set<std::string> attr_names_;
    std::unordered_set <TokenType> operators_;

    void InitializeKeywords();
    bool HasKeyword(std::string keyword);
    void MatchKeyword(std::string keyword);

public:
    QueryLexer();

    void FeedQuery(const std::string& query_string_);

    bool HasDesignEntity();
    std::string MatchDesignEntityKeyword();

    bool HasIdentity();
    std::string MatchIdentity();

    bool HasEndOfDeclarationStatement();
    void MatchEndOfDeclarationStatement();

    

    bool HasSelectKeyword();
    void MatchSelectKeyword();

    bool HasReferenceKeyword();
    std::string MatchReferenceKeyword();

    bool HasLeftBrace();
    void MatchLeftBrace();

    bool HasRightBrace();
    void MatchRightBrace();

    bool HasLeftAngle();
    void MatchLeftAngle();

    bool HasRightAngle();
    void MatchRightAngle();

    bool HasComma();
    void MatchComma();

    bool HasHashtag();
    void MatchHashtag();

    bool HasInteger();
    int MatchInteger();

    bool HasUnderScore();
    void MatchUnderScore();

    bool HasFullStop();
    void MatchFullStop();

    bool HasEqualSign();
    void MatchEqualSign();

    bool HasPatternKeyword();
    void MatchPatternKeyword();

    bool HasWithKeyword();
    void MatchWithKeyword();

    bool HasAndKeyword();
    void MatchAndKeyword();

    bool HasBooleanKeyword();
    void MatchBooleanKeyword();

    bool HasMoreTokens();

    bool HasQuotationMarks();
    void MatchQuotationMarks();

    bool HasOperator();
    std::string MatchOperator();

    bool HasSuchThatKeywords();
    void MatchSuchThatKeywords();

    bool HasAttrName();
    std::string MatchAttrName();

    string GenerateErrorMessage(string expected);
    string GenerateErrorMessage(string expected, string actual);

    std::string PeekNextToken(int number_tokens_);

    bool IsCurrentTokenOfType(TokenType);
};
#endif


