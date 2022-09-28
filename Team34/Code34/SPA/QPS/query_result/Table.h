#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Table {
private:
	std::vector<std::string> fields_;

	std::vector<std::unordered_map<std::string, std::string>> rows_;

	int GetNumOfRows() { return rows_.size(); };
	
	int GetNumOfCols() { return fields_.size(); };

	std::vector<std::string> GetCommonFields(std::shared_ptr<Table> that);

	std::string ComputeHashkey(
		std::vector<std::string> common_fields,
		std::unordered_map<std::string, std::string> row
	);
		
	std::shared_ptr<Table> CrossProductJoin(std::shared_ptr<Table> that);

	std::shared_ptr<Table> HashJoin(std::shared_ptr<Table> that, std::vector<std::string> common_fields);

public:
	std::shared_ptr<Table> Join(std::shared_ptr<Table> that);

	Table(std::vector<std::string> fields, std::vector<std::unordered_map<std::string, std::string>> rows)
		: fields_{ fields }, rows_{ rows } {};
};