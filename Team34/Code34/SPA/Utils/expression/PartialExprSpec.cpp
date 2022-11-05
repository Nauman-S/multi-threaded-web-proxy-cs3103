#include "PartialExprSpec.h"

#include <string>

#include "../../Utils/algo/PostfixConverter.h"

using std::string;


bool PartialExprSpec::IsMatch(Expr& expr) {
    string& full_expr = expr.GetPostfix();
    int fullstr_len = full_expr.size();
    int substr_len = post_expr_.size();
    bool is_sub_expr{ false };

    int pos = full_expr.find(post_expr_, 0);
    while (pos != string::npos && pos < fullstr_len) {
        if ((pos == 0 || full_expr[pos - 1] == PostfixConverter::DELIM) &&
            (pos + substr_len == fullstr_len || full_expr[pos + substr_len] == PostfixConverter::DELIM)) {
            is_sub_expr = true;
            break;
        }
        pos = full_expr.find(post_expr_, pos + substr_len);
    }

    return is_sub_expr;
}
