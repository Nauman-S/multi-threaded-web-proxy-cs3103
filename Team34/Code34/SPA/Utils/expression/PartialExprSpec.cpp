#include "PartialExprSpec.h"

bool PartialExprSpec::IsMatch(Expr expr)
{
	string full_expr = expr.GetPostfix();
	int fullstr_len = full_expr.size();
	int substr_len = post_expr_.length();
	auto is_sub_expr{ false };
	int pos = full_expr.find(post_expr_, 0);

	while (pos < fullstr_len) {
		
		if ((pos == 0 || full_expr[pos - 1] == ' ') && (pos + substr_len == fullstr_len || full_expr[pos + substr_len] == ' ')) {
			is_sub_expr = true;
			break;
		}
		pos = full_expr.find(post_expr_, pos + 1);
	}

	return is_sub_expr;

}
