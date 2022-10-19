#pragma once

/*
* This enum class works as a type contract between ReadPKBManager and DataRetriever.
* To allow ReadPKBManager to get or filter return results as indicated by DataRetriever.
*
* Design decision:
*
*/
enum class RefType {
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

