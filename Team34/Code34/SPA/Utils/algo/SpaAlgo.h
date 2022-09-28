#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "../../QPS/query_result/SetRes.h"
#include "../../QPS/query_result/TableRes.h"


class SpaAlgo
{
public:
	static std::string InfixToPostfix(std::string infix);

	static std::string InfixToPostfix2(std::string& infix);

	static std::shared_ptr<std::vector<std::string>> SpaAlgo::Split(std::string& str, char delim);

	static std::shared_ptr<SetRes> HashJoinSets(std::shared_ptr<SetRes> set1, std::shared_ptr<SetRes> set2);

	static std::pair<std::shared_ptr<SetRes>, std::shared_ptr<TableRes>> HashJoinSetWithTable(std::shared_ptr<SetRes> set, std::shared_ptr<TableRes> table);

	static std::shared_ptr<std::vector<std::vector<std::string>>> HashJoinTables(std::shared_ptr<TableRes> table1, std::shared_ptr<TableRes> table2);

	static std::shared_ptr<TableRes> JoinTablesOfTwoCommonColumns(std::shared_ptr<TableRes> table1, std::shared_ptr<TableRes> table2);

protected:
	static std::unordered_map<char, int> precedence_;
	static std::unordered_map<std::string, int> precedence2_;
};

