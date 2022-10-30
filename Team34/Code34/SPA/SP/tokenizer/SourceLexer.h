#pragma once

#include <fstream>
#include <set>
#include <map>
#include <memory>
#include <vector>
#include <string>

#include "..\..\Utils\tokenizer\Tokenizer.h"
#include "..\..\Utils\tokenizer\Token.h"
#include "SourceToken.h"

class SourceLexer {
public:
    explicit SourceLexer(const std::string&);

    std::shared_ptr<std::vector<SourceToken>> GetAllTokens();

private:
    std::ifstream file_stream_;
    Tokenizer tokenizer_;
    // Temp buffer to store retrieved tokens when doing lookahead
    std::vector<Token> buffer_;

    SourceToken ConstructSourceToken();
    bool HasNextToken();
    Token GetNextToken();

    // Map of allowed source tokens
    static const std::map<std::string, SourceTokenType> allowed_tokens_;
    bool IsValidToken(const std::string&);
    SourceTokenType GetValidTokenType(const std::string&);

    // Set of character that signifies start of possible multi char token
    static const std::set<std::string> multi_char_tokens_starter_;
    bool IsMultiTokenStarter(Token&);
    Token CombineMultiToken(Token&);
};

