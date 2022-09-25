#pragma once
enum class RefType
{
	kProcRef,
	kVarRef,
	kConstRef,
	kStmtRef,
	kAssignRef,
	kCallRef,
	kIfRef,
	kWhileRef,
	kReadRef,
	kPrintRef,
	kUnknown
};

