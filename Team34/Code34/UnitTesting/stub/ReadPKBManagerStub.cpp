#include "stdafx.h"
#include "ReadPKBManagerStub.h"

#include <memory>
#include <unordered_set>

#include "../../SPA/Utils/type/TypeDef.h"
#include "../../SPA/PKB/ReadPKBManager.h"

using std::shared_ptr;
using std::make_shared;
using std::unordered_set;
using std::vector;
using std::pair;


/*
	Stub info for Uses:
	func2 uses y
	statement 5 uses y
*/

const std::shared_ptr<std::unordered_set<Variable>> ReadPKBManagerStub::GetAllVariables()
{
	shared_ptr<unordered_set<Variable>> res = make_shared<unordered_set<Variable>>();
	res->insert("x");
	res->insert("y");
	res->insert("z");

	return res;
}

bool ReadPKBManagerStub::IsVariable(Variable var) {

	return var == "z" || var == "y" || var == "x";
}

bool ReadPKBManagerStub::IsProcedure(Procedure proc) {
	return proc == "Foo1" || proc == "bar" || proc == "Nine";
}
const std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetAllProcedures() {
	std::shared_ptr<std::unordered_set<Procedure>> procs = std::make_shared<std::unordered_set<Procedure>>();
	procs->insert("Foo1");
	procs->insert("bar");
	procs->insert("Nine");

	return procs;
}

bool ReadPKBManagerStub::CheckCalls(Procedure caller, Procedure callee) {
	if (caller == "Foo1" && callee == "bar") {
		return true;
	} else if (caller == "bar" && callee == "Nine") {
		return true;
	}
	return false;
}

bool ReadPKBManagerStub::IsCallsStoreEmpty() {
	return false;
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetCalleeFromCaller(Procedure caller) {
	std::shared_ptr<std::unordered_set<Procedure>> callee = std::make_shared<std::unordered_set<Procedure>>();
	if (caller == "Foo1") {
		callee->insert("bar");
	} else if (caller == "bar") {
		callee->insert("Nine");
	}
	
	return callee;
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetCallerFromCallee(Procedure callee) {
	std::shared_ptr<std::unordered_set<Procedure>> caller = std::make_shared<std::unordered_set<Procedure>>();
	if (callee == "bar") {
		caller->insert("Foo1");
	} else if (callee == "Nine") {
		caller->insert("bar");
	}

	return caller;
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetAllCallers() {
	std::shared_ptr<std::unordered_set<Procedure>> caller = std::make_shared<std::unordered_set<Procedure>>();
	caller->insert("Foo1");
	caller->insert("bar");
	return caller;
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetAllCallees() {
	std::shared_ptr<std::unordered_set<Procedure>> callee = std::make_shared<std::unordered_set<Procedure>>();
	callee->insert("bar");
	callee->insert("Nine");
	return callee;
}

std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> ReadPKBManagerStub::GetAllCallsRelations() {
	std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> calls_relations = std::make_shared<std::vector<std::pair<Procedure, Procedure>>>();
	calls_relations->push_back(std::make_pair("Foo1", "bar"));
	calls_relations->push_back(std::make_pair("bar", "nine"));

	return calls_relations;
}

bool ReadPKBManagerStub::CheckCallsT(Procedure caller, Procedure callee) {
	if (caller == "Foo1" ) {
		return callee == "bar" || callee == "Nine";
	} else if (caller == "bar") {
		return callee == "Nine";
	}
	return false;
}
std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetAllCalleeFromCaller(Procedure caller) {
	std::shared_ptr<std::unordered_set<Procedure>> callee = std::make_shared<std::unordered_set<Procedure>>();
	if (caller == "Foo1") {
		callee->insert("bar");
		callee->insert("Nine");
		return callee;
	} else if (caller == "bar") {
		callee->insert("Nine");
		return callee;
	}
	return callee;
}
std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetAllCallerFromCallee(Procedure callee) {
	std::shared_ptr<std::unordered_set<Procedure>> caller = std::make_shared<std::unordered_set<Procedure>>();
	if (callee == "Nine") {
		caller->insert("Foo1");
		caller->insert("bar");
	} else if (callee == "bar") {
		caller->insert("Foo1");
	}
	return caller;
}
std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> ReadPKBManagerStub::GetAllCallsTRelations() {
	std::shared_ptr<std::vector<std::pair<Procedure, Procedure>>> calls_relations = std::make_shared<std::vector<std::pair<Procedure, Procedure>>>();
	calls_relations->push_back(std::make_pair("Foo1", "bar"));
	calls_relations->push_back(std::make_pair("bar", "nine"));
	calls_relations->push_back(std::make_pair("Foo1", "nine"));

	return calls_relations;
}

std::shared_ptr<RefType> ReadPKBManagerStub::GetStatementType(StmtNum stmt_num)
{
	if (stmt_num == 2 || stmt_num == 4 || stmt_num == 5 || stmt_num == 6) {
		return std::make_shared<RefType>(RefType::kAssignRef);
	} else if (stmt_num == 1) {
		return std::make_shared<RefType>(RefType::kWhileRef);
	} else if (stmt_num == 3) {
		return std::make_shared<RefType>(RefType::kIfRef);
	} else if (stmt_num == 7 || stmt_num == 8 || stmt_num == 9) {
		return std::make_shared<RefType>(RefType::kCallRef);
	}

	return nullptr;
}
std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetStatementsByType(RefType type) {
	std::shared_ptr<std::unordered_set<StmtNum>> statements = std::make_shared <std::unordered_set<StmtNum>> ();
	if (type == RefType::kWhileRef) {
		statements->insert(1);
		return statements;
	} else if (type == RefType::kAssignRef) {
		statements->insert(2);
		statements->insert(4);
		statements->insert(5);
		statements->insert(6);
		return statements;
	} else if (type == RefType::kCallRef) {
		statements->insert(7);
		statements->insert(8);
		statements->insert(9);
		return statements;
	} else if (type == RefType::kIfRef) {
		statements->insert(3);
		return statements;
	} else if (type == RefType::kStmtRef) {
		statements->insert(1);
		statements->insert(2);
		statements->insert(3);
		statements->insert(4);
		statements->insert(5);
		statements->insert(6);
		statements->insert(7);
		statements->insert(8);
		statements->insert(9);
		return statements;
	}

	return statements;
 }
std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllStatements() {
	std::shared_ptr<std::unordered_set<StmtNum>> statements = std::make_shared <std::unordered_set<StmtNum>>();
	statements->insert(1);
	statements->insert(2);
	statements->insert(3);
	statements->insert(4);
	statements->insert(5);
	statements->insert(6);
	statements->insert(7);
	statements->insert(8);
	statements->insert(9);
	return statements;
}
 std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetCallsStatementFromProcedure(Procedure proc) {
	 std::shared_ptr<std::unordered_set<StmtNum>> statements = std::make_shared <std::unordered_set<StmtNum>>();
	 if (proc == "main") {
		 statements->insert(1);
		 statements->insert(2);
		 statements->insert(3);
		 statements->insert(4);
		 statements->insert(5);
		 statements->insert(6);
	 } else if (proc == "Foo1") {
		 statements->insert(7);
	 } else if (proc == "") {
		 statements->insert(8);
		 statements->insert(9);
	 }
	 return statements;
}

bool ReadPKBManagerStub::CheckUses(StmtNum stmt_num, Variable var)
{
	if (stmt_num == 5 && var == "y") {
		return true;
	}

	return false;
}

bool ReadPKBManagerStub::CheckUses(Procedure proc_name, Variable var)
{
	if (proc_name == "func2" && var == "y") {
		return true;
	}

	return false;
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManagerStub::GetUsesVarByStmtNum(StmtNum stmt_num)
{
	shared_ptr<unordered_set<Variable>> res = make_shared<unordered_set<Variable>>();
	if (stmt_num == 5) {
		res->insert("y");
	}

	return res;
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManagerStub::GetUsesVarByProcName(Procedure proc_name)
{
	shared_ptr<unordered_set<Variable>> res = make_shared<unordered_set<Variable>>();
	if (proc_name == "func2") {
		res->insert("y");
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetUsesStmtNumByVar(Variable var, RefType stmt_type)
{
	shared_ptr<unordered_set<StmtNum>> res = make_shared<unordered_set<StmtNum>>();
	if (var == "y") {
		res->insert(5);
	}

	return res;
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetUsesProcNameByVar(Variable var)
{
	shared_ptr<unordered_set<Procedure>> res = make_shared<unordered_set<Procedure>>();
	if (var == "y") {
		res->insert("func2");
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllUsesStatements(RefType stmt_type)
{
	shared_ptr<unordered_set<StmtNum>> res = make_shared<unordered_set<StmtNum>>();
	res->insert(5);

	return res;
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetAllUsesProcedures()
{
	shared_ptr<unordered_set<Procedure>> res = make_shared<unordered_set<Procedure>>();
	res->insert("func2");

	return res;
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ReadPKBManagerStub::GetAllSVUses()
{
	shared_ptr<vector<pair<StmtNum, Variable>>> res = make_shared<vector<pair<StmtNum, Variable>>>();
	res->push_back({ 5, "y" });

	return res;
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> ReadPKBManagerStub::GetAllPVUses()
{
	shared_ptr<vector<pair<Procedure, Variable>>> res = make_shared<vector<pair<Procedure, Variable>>>();
	res->push_back({ "func2", "y" });

	return res;
}

/*
	Stub info for Modifies:
	func1 modifies x
	statement 5 modifies x
*/
bool ReadPKBManagerStub::CheckModifies(StmtNum stmt_num, Variable var)
{
	if (stmt_num == 5 && var == "x") {
		return true;
	}

	return false;
}

bool ReadPKBManagerStub::CheckModifies(Procedure proc_name, Variable var)
{
	if (proc_name == "func1" && var == "x") {
		return true;
	}

	return false;
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManagerStub::GetModifiesVarByStmtNum(StmtNum stmt_num)
{
	shared_ptr<unordered_set<Variable>> res = make_shared<unordered_set<Variable>>();
	if (stmt_num == 5) {
		res->insert("x");
	}

	return res;
}

std::shared_ptr<std::unordered_set<Variable>> ReadPKBManagerStub::GetModifiesVarByProcName(Procedure proc_name)
{
	shared_ptr<unordered_set<Variable>> res = make_shared<unordered_set<Variable>>();
	if (proc_name == "func1") {
		res->insert("x");
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetModifiesStmtNumByVar(Variable var, RefType stmt_type)
{
	shared_ptr<unordered_set<StmtNum>> res = make_shared<unordered_set<StmtNum>>();
	if (var == "x") {
		res->insert(5);
	}

	return res;
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetModifiesProcNameByVar(Variable var)
{
	shared_ptr<unordered_set<Procedure>> res = make_shared<unordered_set<Procedure>>();
	if (var == "x") {
		res->insert("func1");
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllModifiesStatements(RefType stmt_type)
{
	shared_ptr<unordered_set<StmtNum>> res = make_shared<unordered_set<StmtNum>>();
	res->insert(5);

	return res;
}

std::shared_ptr<std::unordered_set<Procedure>> ReadPKBManagerStub::GetAllModifiesProcedures()
{
	shared_ptr<unordered_set<Procedure>> res = make_shared<unordered_set<Procedure>>();
	res->insert("func1");

	return res;
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> ReadPKBManagerStub::GetAllSVModifies()
{
	shared_ptr<vector<pair<StmtNum, Variable>>> res = make_shared<vector<pair<StmtNum, Variable>>>();
	res->push_back({ 5, "x" });

	return res;
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> ReadPKBManagerStub::GetAllPVModifies()
{
	shared_ptr<vector<pair<Procedure, Variable>>> res = make_shared<vector<pair<Procedure, Variable>>>();
	res->push_back({ "func1", "x"});

	return res;
}

bool ReadPKBManagerStub::CheckFollows(StmtNum left, StmtNum right)
{
	if (left == 2 && right == 3) {
		return true;
	}

	return false;
}

bool ReadPKBManagerStub::IsFollowsStoreEmpty()
{
	return false;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetSuccessorStmtFromStmt(StmtNum stmt, RefType successor_type)
{
	auto res = make_shared<unordered_set<int>>();
	if (stmt == 2) {
		res->insert(3);
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetPredecessorStmtFromStmt(StmtNum stmt, RefType predecessor_type)
{
	auto res = make_shared<unordered_set<int>>();
	if (stmt == 3) {
		res->insert(2);
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllSuccessorStmts(RefType successor_type)
{
	auto res = make_shared<unordered_set<int>>();
	res->insert(3);
	res->insert(6);

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllPredecessorStmts(RefType predecessor_type)
{
	auto res = make_shared<unordered_set<int>>();
	res->insert(2);

	return res;
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManagerStub::GetAllFollowsRelations()
{
	auto res = make_shared<vector<pair<int, int>>>();
	res->push_back({ 2,3 });

	return res;
}

bool ReadPKBManagerStub::CheckFollowsT(StmtNum left, StmtNum right)
{
	if (left == 2 && right == 6) {
		return true;
	}

	return false;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllSuccessorStmtsFromStmt(StmtNum stmt, RefType successor_type)
{
	auto res = make_shared<unordered_set<int>>();
	if (stmt == 2) {
		res->insert(6);
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllPredecessorStmtsFromStmt(StmtNum stmt, RefType successor_type)
{
	auto res = make_shared<unordered_set<int>>();
	if (stmt == 6) {
		res->insert(2);
	}

	return res;
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManagerStub::GetAllFollowsTRelations()
{
	auto res = make_shared<vector<pair<int, int>>>();
	res->push_back({ 2, 6 });

	return res;
}

bool ReadPKBManagerStub::CheckParent(StmtNum parent, StmtNum child)
{
	if (parent == 1 && child == 2) {
		return true;
	}

	return false;
}

bool ReadPKBManagerStub::IsParentStoreEmpty()
{
	return false;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetChildrenFromStmt(StmtNum parent, RefType children_type)
{
	auto res = make_shared<unordered_set<int>>();
	if (parent == 1) {
		res->insert(2);
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetParentFromStmt(StmtNum child, RefType parent_type)
{
	auto res = make_shared<unordered_set<int>>();
	if (child == 2) {
		res->insert(1);
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllChildren(RefType children_type)
{
	auto res = make_shared<unordered_set<int>>();
	res->insert(2);
	res->insert(4);

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllParents(RefType parent_type)
{
	auto res = make_shared<unordered_set<int>>();
	res->insert(1);

	return res;
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManagerStub::GetAllParentRelations()
{
	auto res = make_shared<vector<pair<int, int>>>();
	res->push_back({ 1,2 });

	return res;
}

bool ReadPKBManagerStub::CheckParentT(StmtNum parent, StmtNum child)
{
	if (parent == 1 && child == 4) {
		return true;
	}

	return false;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllChildrenFromStmt(StmtNum stmt, RefType children_type)
{
	auto res = make_shared<unordered_set<int>>();
	if (stmt == 1) {
		res->insert(4);
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> ReadPKBManagerStub::GetAllParentsFromStmt(StmtNum stmt, RefType parent_type)
{
	auto res = make_shared<unordered_set<int>>();
	if (stmt == 4) {
		res->insert(1);
	}

	return res;
}

std::shared_ptr<std::vector<std::pair<StmtNum, StmtNum>>> ReadPKBManagerStub::GetAllParentTRelations()
{
	auto res = make_shared<vector<pair<int, int>>>();
	res->push_back({ 1,4 });

	return res;
}