#pragma once

#include <string>
#include <unordered_map>
#include <memory>


class PostfixConverter {
private:
    enum class PrecedenceLevel {
        kLevel1 = 1,
        kLevel2 = 2,
    };

    // Define operators.
    std::string plus{ "+" };
    std::string minus{ "-" };
    std::string multiply{ "*" };
    std::string divide{ "/" };
    std::string modulo{ "%" };
    std::string left_bracket{ "(" };
    std::string right_bracket{ ")" };

protected:
    std::unordered_map<std::string, PrecedenceLevel> precedence_;

    std::shared_ptr<std::vector<std::string>> Split(std::string& str, char delim);

public:
    PostfixConverter() : precedence_{
            { plus, PrecedenceLevel::kLevel1 },
            { minus, PrecedenceLevel::kLevel1 },
            { multiply, PrecedenceLevel::kLevel2 },
            { divide, PrecedenceLevel::kLevel2 },
            { modulo, PrecedenceLevel::kLevel2 }
    } {
    };

    static const char DELIM = ' ';

    std::string InfixToPostfix(std::string& infix);
};

