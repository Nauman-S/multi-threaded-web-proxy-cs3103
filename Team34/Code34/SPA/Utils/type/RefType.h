#pragma once

/*
* This enum class works as a type contract between ReadPKBManager and DataRetriever.
* To allow ReadPKBManager to get or filter return results as indicated by DataRetriever.
*
* Design decision:
* It is controversial that using enum classes breaks OCP.
* An alternative way to achieve the same purpose is to use inheritance by creating 1 class
* for each RefType and use polymorphism to determine the runtime type.
* However, the PKB component is utilising enum of RefType as a key to hash and index within
* underlying data structures found in StatementManager. This is a simple and effective approach
* in handling retrieval of data within the PKB component. While using inheritance would work,
* it would be overcomplicating the problem as object types would not be suitable to be used as a
* key in a map.
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

