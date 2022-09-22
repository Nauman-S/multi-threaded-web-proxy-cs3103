#pragma once
enum class RelType
{
	kStmtStmtRel,
	kStmtVarRel,
	kProcVarRel,
	kProcProcRel,
	kUsesSRel,
	kUsesPRel,
	kModifiesSRel,
	kModifiesPRel,
	kParentRel,
	kParentTRel,
	kFollowsRel,
	kFollowsTRel,
	kCallsRel,
	kCallsTRel,
	kNextRel,
	kNextTRel,
	kAffectsRel,
	kAffectsTRel,
};

