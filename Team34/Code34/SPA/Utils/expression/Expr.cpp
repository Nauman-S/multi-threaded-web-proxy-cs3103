#include "Expr.h"
#include "../algo/SpaAlgo.h"

Expr::Expr(string infix_expr)
{
	post_expr_ = SpaAlgo::InfixToPostfix(infix_expr);
}