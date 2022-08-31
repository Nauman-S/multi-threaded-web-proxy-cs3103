#pragma once

#include <fstream>
#include <set>
#include <map>

#include "..\Utils\Tokenizer.h"
#include "..\Utils\Token.h"
#include "SourceToken.h"

class SourceLexer {
private:
    std::ifstream file_stream_;
    Tokenizer tokenizer_;
    // Temp buffer to store retrieved tokens when doing lookahead
    std::vector<Token> buffer_;

    SourceToken ConstructSourceToken();
    bool HasNextToken();
    Token GetNextToken();
    Token CombineMultiToken(Token);

    bool IsMultiTokenStarter(const Token&);
    bool IsKeyword(const Token&);
    bool IsValidToken(const std::string&);
    SourceTokenType GetKeywordType(const std::string&);
    SourceTokenType GetValidTokenType(const std::string&);

    static const std::map<std::string, SourceTokenType> keywords_;
    static const std::map<std::string, SourceTokenType> allowed_tokens_;
    // Set of character that signifies start of possible multi char token
    const static std::set<std::string> multi_char_tokens_starter_;

public:
    SourceLexer(const std::string&);

    std::vector<SourceToken> GetAllTokens();
};

