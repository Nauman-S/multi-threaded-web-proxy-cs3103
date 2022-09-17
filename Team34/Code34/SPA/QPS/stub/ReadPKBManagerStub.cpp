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
bool CheckUses(StmtNum stmt_num, Variable var)
{
	if (stmt_num == 5 && var == "y") {
		return true;
	}

	return false;
}

bool CheckUses(Procedure proc_name, Variable var)
{
	if (proc_name == "func2" && var == "y") {
		return true;
	}

	return false;
}

std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByStmtNum(StmtNum stmt_num)
{
	shared_ptr<unordered_set<Variable>> res;
	if (stmt_num == 5) {
		res->insert("y");
	}

	return res;
}

std::shared_ptr<std::unordered_set<Variable>> GetUsesVarByProcName(Procedure proc_name)
{
	shared_ptr<unordered_set<Variable>> res;
	if (proc_name == "func2") {
		res->insert("y");
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> GetUsesStmtNumByVar(Variable var)
{
	shared_ptr<unordered_set<StmtNum>> res;
	if (var == "y") {
		res->insert(5);
	}

	return res;
}

std::shared_ptr<std::unordered_set<Procedure>> GetUsesProcNameByVar(Variable var)
{
	shared_ptr<unordered_set<Procedure>> res;
	if (var == "y") {
		res->insert("func2");
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> GetAllUsesStatements()
{
	shared_ptr<unordered_set<StmtNum>> res;
	res->insert(5);

	return res;
}

std::shared_ptr<std::unordered_set<Procedure>> GetAllUsesProcedures()
{
	shared_ptr<unordered_set<Procedure>> res;
	res->insert("func2");

	return res;
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVUses()
{
	shared_ptr<vector<pair<StmtNum, Variable>>> res;
	res->push_back({ 5, "y" });

	return res;
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVUses()
{
	shared_ptr<vector<pair<Procedure, Variable>>> res;
	res->push_back({ "func2", "y" });

	return res;
}

/*
	Stub info for Modifies:
	func1 modifies x
	statement 5 modifies x
*/
bool CheckModifies(StmtNum stmt_num, Variable var)
{
	if (stmt_num == 5 && var == "x") {
		return true;
	}

	return false;
}

bool CheckModifies(Procedure proc_name, Variable var)
{
	if (proc_name == "func1" && var == "x") {
		return true;
	}

	return false;
}

std::shared_ptr<Variable> GetModifiesVarByStmtNum(StmtNum stmt_num)
{
	if (stmt_num == 5) {
		return make_shared<Variable>("x");
	}

	return nullptr;
}

std::shared_ptr<std::unordered_set<Variable>> GetModifiesVarByProcName(Procedure proc_name)
{
	shared_ptr<unordered_set<Variable>> res;
	if (proc_name == "func1") {
		res->insert("x");
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> GetModifiesStmtNumByVar(Variable var)
{
	shared_ptr<unordered_set<StmtNum>> res;
	if (var == "x") {
		res->insert(5);
	}

	return res;
}

std::shared_ptr<std::unordered_set<Procedure>> GetModifiesProcNameByVar(Variable var)
{
	shared_ptr<unordered_set<Procedure>> res;
	if (var == "x") {
		res->insert("func1");
	}

	return res;
}

std::shared_ptr<std::unordered_set<StmtNum>> GetAllModifiesStatements()
{
	shared_ptr<unordered_set<StmtNum>> res;
	res->insert(5);

	return res;
}

std::shared_ptr<std::unordered_set<Procedure>> GetAllModifiesProcedures()
{
	shared_ptr<unordered_set<Procedure>> res;
	res->insert("func1");

	return res;
}

std::shared_ptr<std::vector<std::pair<StmtNum, Variable>>> GetAllSVModifies()
{
	shared_ptr<vector<pair<StmtNum, Variable>>> res;
	res->push_back({ 5, "x" });

	return res;
}

std::shared_ptr<std::vector<std::pair<Procedure, Variable>>> GetAllPVModifies()
{
	shared_ptr<vector<pair<Procedure, Variable>>> res;
	res->push_back({ "func1", "x"});

	return res;
}