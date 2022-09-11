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

	static std::shared_ptr<SetRes> HashJoinSets(std::shared_ptr<SetRes> set1, std::shared_ptr<SetRes> set2);

	static std::shared_ptr<TableRes> HashJoinSetWithTable(std::shared_ptr<SetRes> set, std::shared_ptr<TableRes> table);

	// static std::shared_ptr<TableRes> HashJoinTables(std::shared_ptr<TableRes> table1, std::shared_ptr<TableRes> table2);

protected:
	static std::unordered_map<char, int> precedence_;
};

