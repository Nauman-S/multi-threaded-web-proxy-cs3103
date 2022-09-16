#include "RelationStubFactory.h"

#include <vector>
#include <memory>

#include "../../../SPA/QPS/relation/ModifiesPRel.h"
#include "../../../SPA/QPS/relation/ModifiesSRel.h"
#include "../../../SPA/QPS/relation/UsesPRel.h"
#include "../../../SPA/QPS/relation/UsesSRel.h"
#include "../../../SPA/QPS/relation/FollowsRel.h"
#include "../../../SPA/QPS/relation/FollowsTRel.h"
#include "../../../SPA/QPS/relation/ParentRel.h"
#include "../../../SPA/QPS/relation/ParentTRel.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;


std::shared_ptr<std::vector<std::shared_ptr<ModifiesPRel>>> RelationStubFactory::GetModifiesPRelStubs()
{
	// (proc_name, var_name)

	// (proc_name, synonym)

	// (synonym, var_name)

	// (synonym, synonym)

	// (proc_name, wildcard)

	// (synonym, wildcard)
}

std::shared_ptr<std::vector<std::shared_ptr<ModifiesSRel>>> GetModifiesSRelStubs()
{
	// (stmt_num, var_name)

	// (stmt_num, synonym)

	// (synonym, var_name)

	// (synonym, synonym)

	// (stmt_num, wildcard)

	// (synonym, wildcard)
}

std::shared_ptr<std::vector<std::shared_ptr<UsesPRel>>> GetUsesPRelStubs()
{
	// (proc_name, var_name)

	// (proc_name, synonym)

	// (synonym, var_name)

	// (synonym, synonym)

	// (proc_name, wildcard)

	// (synonym, wildcard)
}

std::shared_ptr<std::vector<std::shared_ptr<UsesSRel>>> GetUsesSRelStubs()
{
	// (stmt_num, var_name)

	// (stmt_num, synonym)

	// (synonym, var_name)

	// (synonym, synonym)

	// (stmt_num, wildcard)

	// (synonym, wildcard)
}

std::shared_ptr<std::vector<std::shared_ptr<FollowsRel>>> GetFollowsRelStubs()
{
	// (stmt_num, stmt_num)

	// (synonym, stmt_num)

	// (stmt_num, synonym)

	// (synonym, synonym)

	// (wildcard, stmt_num)

	// (wildcard, synonym)

	// (stmt_num, wildcard)

	// (stmt_num, synonym)

	// (wildcard, wildcard)
}

std::shared_ptr<std::vector<std::shared_ptr<FollowsTRel>>> GetFollowsTRelStubs()
{
	// (stmt_num, stmt_num)

	// (synonym, stmt_num)

	// (stmt_num, synonym)

	// (synonym, synonym)

	// (wildcard, stmt_num)

	// (wildcard, synonym)

	// (stmt_num, wildcard)

	// (stmt_num, synonym)

	// (wildcard, wildcard)
}

std::shared_ptr<std::vector<std::shared_ptr<ParentRel>>> GetParentRelStubs()
{
	// (stmt_num, stmt_num)

	// (synonym, stmt_num)

	// (stmt_num, synonym)

	// (synonym, synonym)

	// (wildcard, stmt_num)

	// (wildcard, synonym)

	// (stmt_num, wildcard)

	// (stmt_num, synonym)

	// (wildcard, wildcard)
}

std::shared_ptr<std::vector<std::shared_ptr<ParentTRel>>> GetParentTRelStubs()
{
	// (stmt_num, stmt_num)

	// (synonym, stmt_num)

	// (stmt_num, synonym)

	// (synonym, synonym)

	// (wildcard, stmt_num)

	// (wildcard, synonym)

	// (stmt_num, wildcard)

	// (stmt_num, synonym)

	// (wildcard, wildcard)
}