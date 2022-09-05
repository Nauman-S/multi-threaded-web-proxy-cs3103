#include "ExactExprSpec.h"

bool ExactExprSpec::IsMatch(Expr expr)
{
	return post_expr_ == expr.GetPostfix();
}
