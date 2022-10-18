#pragma once

enum class ClauseType {
	kWith,

	kAssignPattern,
	kIfPattern,
	kWhilePattern,

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