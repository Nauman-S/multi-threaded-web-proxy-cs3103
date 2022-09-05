#include "ExprSpec.h"
#include "../algo/SpaAlgo.h"
void ExprSpec::ExprSepc(std::string infix_expr)
{
	post_expr_ = SpaAlgo::InfixToPostfix(infix_expr);
}
