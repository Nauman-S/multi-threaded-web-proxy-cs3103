#include "ReadPKBManagerStub.h"

#include <memory>
#include <unordered_set>

#include "../../Utils/type/TypeDef.h"
#include "../../PKB/ReadPKBManager.h"

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
std::shared_ptr<RefType> ReadPKBManagerStub::GetStatementType(StmtNum stmt_num)
{
	if (stmt_num == 2 || stmt_num == 4 || stmt_num == 5 || stmt_num == 6) {
		return std::make_shared<RefType>(RefType::kAssignRef);
	}
	else if (stmt_num == 1) {
		return std::make_shared<RefType>(RefType::kWhileRef);
	}
	else if (stmt_num == 3) {
		return std::make_shared<RefType>(RefType::kIfRef);
	}

	return nullptr;
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

const std::shared_ptr<std::unordered_set<Variable>> ReadPKBManagerStub::GetAllVariables()
{
	shared_ptr<unordered_set<Variable>> res = make_shared<unordered_set<Variable>>();
	res->insert("x");
	res->insert("y");
	res->insert("z");

	return res;
}