#include "RelationStubFactory.h"

#include <vector>
#include <memory>

#include "../relation/Rel.h"
#include "../relation/ModifiesPRel.h"
#include "../relation/ModifiesSRel.h"
#include "../relation/UsesPRel.h"
#include "../relation/UsesSRel.h"
#include "../relation/FollowsRel.h"
#include "../relation/FollowsTRel.h"
#include "../relation/ParentRel.h"
#include "../relation/ParentTRel.h"
#include "../reference/ProcRef.h"
#include "../reference/VarRef.h"
#include "../reference/StmtRef.h"
#include "../reference/AssignRef.h"
#include "../reference/IfRef.h"
#include "../reference/WhileRef.h"
#include "../reference/ValType.h"
#include "../../Utils/type/RefType.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;


std::shared_ptr<Rel> RelationStubFactory::GetModifiesP_proc_name_var_name()
{
	// (proc_name, var_name)
	shared_ptr<ProcRef> proc_name_ref = make_shared<ProcRef>(ValType::kProcName, "func1");
	shared_ptr<VarRef> var_name_ref = make_shared<VarRef>(ValType::kVarName, "x");
	shared_ptr<Rel> proc_name_var_name = make_shared<ModifiesPRel>(proc_name_ref, var_name_ref);

	return proc_name_var_name;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesP_proc_name_var_syn()
{
	// (proc_name, var_syn)
	shared_ptr<ProcRef> proc_name_ref = make_shared<ProcRef>(ValType::kProcName, "func1");
	shared_ptr<VarRef> var_syn_ref = make_shared<VarRef>(ValType::kSynonym, "v1");
	shared_ptr<Rel> proc_name_var_syn = make_shared<ModifiesPRel>(proc_name_ref, var_syn_ref);

	return proc_name_var_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesP_proc_syn_var_name()
{
	// (synonym, var_name)
	shared_ptr<ProcRef> proc_syn_ref = make_shared<ProcRef>(ValType::kSynonym, "p1");
	shared_ptr<VarRef> var_name_ref = make_shared<VarRef>(ValType::kVarName, "x");
	shared_ptr<Rel> proc_syn_var_name = make_shared<ModifiesPRel>(proc_syn_ref, var_name_ref);

	return proc_syn_var_name;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesP_proc_syn_var_syn()
{
	// (synonym, synonym)
	shared_ptr<ProcRef> proc_syn_ref = make_shared<ProcRef>(ValType::kSynonym, "p1");
	shared_ptr<VarRef> var_syn_ref = make_shared<VarRef>(ValType::kSynonym, "v1");
	shared_ptr<Rel> proc_syn_var_syn = make_shared<ModifiesPRel>(proc_syn_ref, var_syn_ref);

	return proc_syn_var_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesP_proc_name_var_wildcard()
{
	// (proc_name, wildcard)
	shared_ptr<ProcRef> proc_name_ref = make_shared<ProcRef>(ValType::kProcName, "func1");
	shared_ptr<VarRef> var_wildcard_ref = make_shared<VarRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> proc_name_var_wildcard = make_shared<ModifiesPRel>(proc_name_ref, var_wildcard_ref);

	return proc_name_var_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesP_proc_syn_var_wildcard()
{
	// (synonym, wildcard)
	shared_ptr<ProcRef> proc_syn_ref = make_shared<ProcRef>(ValType::kSynonym, "p1");
	shared_ptr<VarRef> var_wildcard_ref = make_shared<VarRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> proc_syn_var_wildcard = make_shared<ModifiesPRel>(proc_syn_ref, var_wildcard_ref);
	
	return proc_syn_var_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesS_stmt_num_var_name()
{
	// (stmt_num, var_name)
	shared_ptr<AssignRef> stmt_num_ref = make_shared<AssignRef>(ValType::kLineNum, "5");
	shared_ptr<VarRef> var_name_ref = make_shared<VarRef>(ValType::kVarName, "x");
	shared_ptr<Rel> stmt_num_var_name = make_shared<ModifiesSRel>(stmt_num_ref, var_name_ref);

	return stmt_num_var_name;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesS_stmt_num_var_syn()
{
	// (stmt_num, synonym)
	shared_ptr<AssignRef> stmt_num_ref = make_shared<AssignRef>(ValType::kLineNum, "5");
	shared_ptr<VarRef> var_syn_ref = make_shared<VarRef>(ValType::kSynonym, "v1");
	shared_ptr<Rel> stmt_num_var_syn = make_shared<ModifiesSRel>(stmt_num_ref, var_syn_ref);

	return stmt_num_var_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesS_stmt_syn_var_name()
{
	// (synonym, var_name)
	shared_ptr<AssignRef> stmt_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s1");
	shared_ptr<VarRef> var_name_ref = make_shared<VarRef>(ValType::kVarName, "x");
	shared_ptr<Rel> stmt_syn_var_name = make_shared<ModifiesSRel>(stmt_syn_ref, var_name_ref);

	return stmt_syn_var_name;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesS_stmt_syn_var_syn()
{
	// (synonym, synonym)
	shared_ptr<AssignRef> stmt_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s1");
	shared_ptr<VarRef> var_syn_ref = make_shared<VarRef>(ValType::kSynonym, "v1");
	shared_ptr<Rel> stmt_syn_var_syn = make_shared<ModifiesSRel>(stmt_syn_ref, var_syn_ref);

	return stmt_syn_var_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesS_stmt_num_var_wildcard()
{
	// (stmt_num, wildcard)
	shared_ptr<AssignRef> stmt_num_ref = make_shared<AssignRef>(ValType::kLineNum, "5");
	shared_ptr<VarRef> var_wildcard_ref = make_shared<VarRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_num_var_wildcard = make_shared<ModifiesSRel>(stmt_num_ref, var_wildcard_ref);

	return stmt_num_var_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetModifiesS_stmt_syn_var_wildcard()
{
	// (synonym, wildcard)
	shared_ptr<AssignRef> stmt_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s1");
	shared_ptr<VarRef> var_wildcard_ref = make_shared<VarRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_syn_var_wildcard = make_shared<ModifiesSRel>(stmt_syn_ref, var_wildcard_ref);

	return stmt_syn_var_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesP_proc_name_var_name()
{
	// (proc_name, var_name)
	shared_ptr<ProcRef> proc_name_ref = make_shared<ProcRef>(ValType::kProcName, "func2");
	shared_ptr<VarRef> var_name_ref = make_shared<VarRef>(ValType::kVarName, "y");
	shared_ptr<Rel> proc_name_var_name = make_shared<UsesPRel>(proc_name_ref, var_name_ref);

	return proc_name_var_name;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesP_proc_name_var_syn()
{
	// (proc_name, synonym)
	shared_ptr<ProcRef> proc_name_ref = make_shared<ProcRef>(ValType::kProcName, "func2");
	shared_ptr<VarRef> var_syn_ref = make_shared<VarRef>(ValType::kSynonym, "v2");
	shared_ptr<Rel> proc_name_var_syn = make_shared<UsesPRel>(proc_name_ref, var_syn_ref);

	return proc_name_var_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesP_proc_syn_var_name()
{
	// (synonym, var_name)
	shared_ptr<ProcRef> proc_syn_ref = make_shared<ProcRef>(ValType::kSynonym, "p2");
	shared_ptr<VarRef> var_name_ref = make_shared<VarRef>(ValType::kVarName, "y");
	shared_ptr<Rel> proc_syn_var_name = make_shared<UsesPRel>(proc_syn_ref, var_name_ref);

	return proc_syn_var_name;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesP_proc_syn_var_syn()
{
	// (synonym, synonym)
	shared_ptr<ProcRef> proc_syn_ref = make_shared<ProcRef>(ValType::kSynonym, "p2");
	shared_ptr<VarRef> var_syn_ref = make_shared<VarRef>(ValType::kSynonym, "v2");
	shared_ptr<Rel> proc_syn_var_syn = make_shared<UsesPRel>(proc_syn_ref, var_syn_ref);

	return proc_syn_var_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesP_proc_name_var_wildcard()
{
	// (proc_name, wildcard)
	shared_ptr<ProcRef> proc_name_ref = make_shared<ProcRef>(ValType::kProcName, "func2");
	shared_ptr<VarRef> var_wildcard_ref = make_shared<VarRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> proc_name_var_wildcard = make_shared<UsesPRel>(proc_name_ref, var_wildcard_ref);

	return proc_name_var_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesP_proc_syn_var_wildcard()
{
	// (synonym, wildcard)
	shared_ptr<ProcRef> proc_syn_ref = make_shared<ProcRef>(ValType::kSynonym, "p2");
	shared_ptr<VarRef> var_wildcard_ref = make_shared<VarRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> proc_syn_var_wildcard = make_shared<UsesPRel>(proc_syn_ref, var_wildcard_ref);

	return proc_syn_var_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesS_stmt_num_var_name()
{
	// (stmt_num, var_name)
	shared_ptr<AssignRef> stmt_num_ref = make_shared<AssignRef>(ValType::kLineNum, "5");
	shared_ptr<VarRef> var_name_ref = make_shared<VarRef>(ValType::kVarName, "y");
	shared_ptr<Rel> stmt_num_var_name = make_shared<UsesSRel>(stmt_num_ref, var_name_ref);

	return stmt_num_var_name;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesS_stmt_num_var_syn()
{
	// (stmt_num, var_syn)
	shared_ptr<AssignRef> stmt_num_ref = make_shared<AssignRef>(ValType::kLineNum, "5");
	shared_ptr<VarRef> var_syn_ref = make_shared<VarRef>(ValType::kSynonym, "v2");
	shared_ptr<Rel> stmt_num_var_syn = make_shared<UsesSRel>(stmt_num_ref, var_syn_ref);

	return stmt_num_var_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesS_stmt_syn_var_name()
{
	// (stmt_syn, var_name)
	shared_ptr<AssignRef> stmt_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s1");
	shared_ptr<VarRef> var_name_ref = make_shared<VarRef>(ValType::kVarName, "y");
	shared_ptr<Rel> stmt_syn_var_name = make_shared<UsesSRel>(stmt_syn_ref, var_name_ref);

	return stmt_syn_var_name;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesS_stmt_syn_var_syn()
{
	// (stmt_syn, var_syn)
	shared_ptr<AssignRef> stmt_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s1");
	shared_ptr<VarRef> var_syn_ref = make_shared<VarRef>(ValType::kSynonym, "v2");
	shared_ptr<Rel> stmt_syn_var_syn = make_shared<UsesSRel>(stmt_syn_ref,var_syn_ref);

	return stmt_syn_var_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesS_stmt_num_var_wildcard()
{
	// (stmt_num, wildcard)
	shared_ptr<AssignRef> stmt_num_ref = make_shared<AssignRef>(ValType::kLineNum, "5");
	shared_ptr<VarRef> var_wildcard_ref = make_shared<VarRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_num_var_wildcard = make_shared<UsesSRel>(stmt_num_ref, var_wildcard_ref);

	return stmt_num_var_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetUsesS_stmt_syn_var_wildcard()
{
	// (stmt_syn, var_wildcard)
	shared_ptr<AssignRef> stmt_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s1");
	shared_ptr<VarRef> var_wildcard_ref = make_shared<VarRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_syn_var_wildcard = make_shared<UsesSRel>(stmt_syn_ref, var_wildcard_ref);

	return stmt_syn_var_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollows_stmt_num_stmt_num()
{
	// Follows(2, 3)
	shared_ptr<AssignRef> stmt1_num_ref = make_shared<AssignRef>(ValType::kLineNum, "2");
	shared_ptr<IfRef> stmt2_num_ref = make_shared<IfRef>(ValType::kLineNum, "3");
	shared_ptr<Rel> stmt_num_stmt_num = make_shared<FollowsRel>(stmt1_num_ref, stmt2_num_ref);

	return stmt_num_stmt_num;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollows_stmt_num_stmt_syn()
{
	// Follows(2, 3)
	shared_ptr<AssignRef> stmt1_num_ref = make_shared<AssignRef>(ValType::kLineNum, "2");
	shared_ptr<StmtRef> stmt2_syn_ref = make_shared<StmtRef>(ValType::kSynonym, "s3");
	shared_ptr<Rel> stmt_num_stmt_syn = make_shared<FollowsRel>(stmt1_num_ref, stmt2_syn_ref);

	return stmt_num_stmt_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollows_stmt_syn_stmt_num()
{
	// Follows(2, 3)
	shared_ptr<AssignRef> stmt1_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s2");
	shared_ptr<IfRef> stmt2_num_ref = make_shared<IfRef>(ValType::kLineNum, "3");
	shared_ptr<Rel> stmt_syn_stmt_num = make_shared<FollowsRel>(stmt1_syn_ref, stmt2_num_ref);

	return stmt_syn_stmt_num;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollows_stmt_syn_stmt_syn()
{
	// Follows(2, 3)
	shared_ptr<AssignRef> stmt1_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s2");
	shared_ptr<IfRef> stmt2_syn_ref = make_shared<IfRef>(ValType::kSynonym, "s3");
	shared_ptr<Rel> stmt_syn_stmt_syn = make_shared<FollowsRel>(stmt1_syn_ref, stmt2_syn_ref);

	return stmt_syn_stmt_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollows_stmt_wildcard_stmt_num()
{
	// Follows(2, 3)
	shared_ptr<AssignRef> stmt1_wildcard_ref = make_shared<AssignRef>(ValType::kWildcard, "_");
	shared_ptr<IfRef> stmt2_num_ref = make_shared<IfRef>(ValType::kLineNum, "3");
	shared_ptr<Rel> stmt_wildcard_stmt_num = make_shared<FollowsRel>(stmt1_wildcard_ref, stmt2_num_ref);

	return stmt_wildcard_stmt_num;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollows_stmt_wildcard_stmt_syn()
{
	// Follows(2, 3)
	shared_ptr<AssignRef> stmt1_wildcard_ref = make_shared<AssignRef>(ValType::kWildcard, "_");
	shared_ptr<StmtRef> stmt2_syn_ref = make_shared<StmtRef>(ValType::kSynonym, "s3");
	shared_ptr<Rel> stmt_wildcard_stmt_syn = make_shared<FollowsRel>(stmt1_wildcard_ref, stmt2_syn_ref);

	return stmt_wildcard_stmt_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollows_stmt_num_stmt_wildcard()
{
	// Follows(2, 3)
	shared_ptr<AssignRef> stmt1_num_ref = make_shared<AssignRef>(ValType::kLineNum, "2");
	shared_ptr<IfRef> stmt2_wildcard_ref = make_shared<IfRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_num_stmt_wildcard = make_shared<FollowsRel>(stmt1_num_ref, stmt2_wildcard_ref);

	return stmt_num_stmt_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollows_stmt_syn_stmt_wildcard()
{
	// Follows(2, 3)
	shared_ptr<AssignRef> stmt1_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s2");
	shared_ptr<IfRef> stmt2_wildcard_ref = make_shared<IfRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_syn_stmt_wildcard = make_shared<FollowsRel>(stmt1_syn_ref, stmt2_wildcard_ref);

	return stmt_syn_stmt_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollows_stmt_wildcard_stmt_wildcard()
{
	// Follows(2, 3)
	shared_ptr<AssignRef> stmt1_wildcard_ref = make_shared<AssignRef>(ValType::kWildcard, "_");
	shared_ptr<IfRef> stmt2_wildcard_ref = make_shared<IfRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_wildcard_stmt_wildcard = make_shared<FollowsRel>(stmt1_wildcard_ref, stmt2_wildcard_ref);

	return stmt_wildcard_stmt_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollowsT_stmt_num_stmt_num()
{
	// FollowsT(2,6)
	shared_ptr<AssignRef> stmt1_num_ref = make_shared<AssignRef>(ValType::kLineNum, "2");
	shared_ptr<AssignRef> stmt2_num_ref = make_shared<AssignRef>(ValType::kLineNum, "6");
	shared_ptr<Rel> stmt_num_stmt_num = make_shared<FollowsRel>(stmt1_num_ref, stmt2_num_ref);

	return stmt_num_stmt_num;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollowsT_stmt_num_stmt_syn()
{
	// FollowsT(2, 6)
	shared_ptr<AssignRef> stmt1_num_ref = make_shared<AssignRef>(ValType::kLineNum, "2");
	shared_ptr<AssignRef> stmt2_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s6");
	shared_ptr<Rel> stmt_num_stmt_syn = make_shared<FollowsRel>(stmt1_num_ref, stmt2_syn_ref);

	return stmt_num_stmt_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollowsT_stmt_syn_stmt_num()
{
	// FollowsT(2, 6)
	shared_ptr<AssignRef> stmt1_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s2");
	shared_ptr<AssignRef> stmt2_num_ref = make_shared<AssignRef>(ValType::kLineNum, "6");
	shared_ptr<Rel> stmt_syn_stmt_num = make_shared<FollowsRel>(stmt1_syn_ref, stmt2_num_ref);

	return stmt_syn_stmt_num;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollowsT_stmt_syn_stmt_syn()
{
	// FollowsT(2, 6)
	shared_ptr<AssignRef> stmt1_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s2");
	shared_ptr<AssignRef> stmt2_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s6");
	shared_ptr<Rel> stmt_syn_stmt_syn = make_shared<FollowsRel>(stmt1_syn_ref, stmt2_syn_ref);

	return stmt_syn_stmt_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollowsT_stmt_wildcard_stmt_num()
{
	// FollowsT(2, 6)
	shared_ptr<AssignRef> stmt1_wildcard_ref = make_shared<AssignRef>(ValType::kWildcard, "_");
	shared_ptr<AssignRef> stmt2_num_ref = make_shared<AssignRef>(ValType::kLineNum, "6");
	shared_ptr<Rel> stmt_wildcard_stmt_num = make_shared<FollowsRel>(stmt1_wildcard_ref, stmt2_num_ref);

	return stmt_wildcard_stmt_num;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollowsT_stmt_wildcard_stmt_syn()
{
	// FollowsT(2, 6)
	shared_ptr<AssignRef> stmt1_wildcard_ref = make_shared<AssignRef>(ValType::kWildcard, "_");
	shared_ptr<StmtRef> stmt2_syn_ref = make_shared<StmtRef>(ValType::kSynonym, "s6");
	shared_ptr<Rel> stmt_wildcard_stmt_syn = make_shared<FollowsRel>(stmt1_wildcard_ref, stmt2_syn_ref);

	return stmt_wildcard_stmt_syn;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollowsT_stmt_num_stmt_wildcard()
{
	// FollowsT(2, 6)
	shared_ptr<AssignRef> stmt1_num_ref = make_shared<AssignRef>(ValType::kLineNum, "2");
	shared_ptr<StmtRef> stmt2_wildcard_ref = make_shared<StmtRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_num_stmt_wildcard = make_shared<FollowsRel>(stmt1_num_ref, stmt2_wildcard_ref);

	return stmt_num_stmt_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollowsT_stmt_syn_stmt_wildcard()
{
	// FollowsT(2, 6)
	shared_ptr<AssignRef> stmt1_syn_ref = make_shared<AssignRef>(ValType::kSynonym, "s2");
	shared_ptr<StmtRef> stmt2_wildcard_ref = make_shared<StmtRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_syn_stmt_wildcard = make_shared<FollowsRel>(stmt1_syn_ref, stmt2_wildcard_ref);

	return stmt_syn_stmt_wildcard;
}

std::shared_ptr<Rel> RelationStubFactory::GetFollowsT_stmt_wildcard_stmt_wildcard()
{
	// FollowsT(2, 6)
	shared_ptr<AssignRef> stmt1_wildcard_ref = make_shared<AssignRef>(ValType::kWildcard, "_");
	shared_ptr<AssignRef> stmt2_wildcard_ref = make_shared<AssignRef>(ValType::kWildcard, "_");
	shared_ptr<Rel> stmt_wildcard_stmt_wildcard = make_shared<FollowsRel>(stmt1_wildcard_ref, stmt2_wildcard_ref);

	return stmt_wildcard_stmt_wildcard;
}
