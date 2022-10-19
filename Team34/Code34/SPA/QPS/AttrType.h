#pragma once

/*
* This enum class works jointly with ClauseType and ValType to let DataRetriever aquire
* neccessary information about a Clause (especially With clauses) to call the right PKB API.
*
* Design decision:
* It is controversial that using enum classes and if-else statements in DataRetriever
* breaks OCP.
* An alternative way to achieve the same purpose is to use inheritance by creating 1 class
* for each combination of clause type and value types (e.g. SynonymWildcardNextRel for Next(s,_)),
* which will need a large numnber of simple classes, and also requires a large number of
* overloaded methods in DataRetriever.
* The alternative way adds unneccesssary complexiy to QPS and codebase and is hard to implement,
* so we decide to use the enum + if-else statements approach.
* The regression tests after each new feature implementation also protects the application
* from potential regression due to OCP breaks.
*/

enum class AttrType {
    // temporary type
    kStr,
    kInt,

    kProcName,
    kVarName,
    kStmtNum,
    kConst
};