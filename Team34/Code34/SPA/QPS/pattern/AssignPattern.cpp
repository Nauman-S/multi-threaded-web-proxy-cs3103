#include "AssignPattern.h"
#include "../DataRetriever.h"

std::shared_ptr<ExprSpec> AssignPattern::ExprSpec()
{
    return expr_spec_;
}