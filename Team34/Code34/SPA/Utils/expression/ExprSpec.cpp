#include "ExprSpec.h"
#include "../algo/SpaAlgo.h"

ExprSpec::ExprSpec(std::string infix_expr)
{
	post_expr_ = SpaAlgo::InfixToPostfix(infix_expr);
}
