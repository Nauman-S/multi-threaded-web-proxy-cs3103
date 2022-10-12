#pragma once

#include <string>

class Expr {
protected:
    std::string infix_expr_;
    std::string post_expr_;

public:
    Expr(std::string& infix_str, std::string& postfix_str)
        : infix_expr_{ infix_str }, post_expr_{ postfix_str } {
    };

    std::string& GetInfix() { return infix_expr_; }
    std::string& GetPostfix() { return post_expr_; }
};

