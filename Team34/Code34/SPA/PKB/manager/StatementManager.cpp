#include "StatementManager.h"

void StatementManager::AddStatement(int stmt_num, RefType type)
{
	assert(type != RefType::kConstRef || type != RefType::kVarRef);

}