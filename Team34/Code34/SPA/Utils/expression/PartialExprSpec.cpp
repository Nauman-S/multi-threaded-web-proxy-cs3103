#include "PartialExprSpec.h"

bool PartialExprSpec::IsMatch(Expr expr)
{
	return expr.GetPostfix().find(post_expr_) != string::npos;
}
