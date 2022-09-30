#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <assert.h>

#include "ResWrapper.h"
class Table {
private:
	std::vector<std::string> fields_;

	//std::vector<std::unordered_map<std::string, std::string>> rows_;
	std::unordered_map<std::string, int> field_to_index_map_;

	std::vector<std::vector<std::string>> rows_;

	bool is_empty_;


	std::string GetFieldAtIndex(int idx) {
		assert(idx < fields_.size());
		return fields_.at(idx);
	}

	std::string GetValueInField(std::string field, std::vector<std::string>& row) {
		return row.at(field_to_index_map_.at(field));
	}

	std::vector<std::string> GetCommonFields(std::shared_ptr<Table> that);

	std::string ComputeHashkey(
		std::vector<std::string> common_fields,
		std::vector<std::string> row
	);
		
	std::shared_ptr<Table> CrossProductJoin(std::shared_ptr<Table> that);

	std::shared_ptr<Table> HashJoin(std::shared_ptr<Table> that, std::vector<std::string> common_fields);

public:
	Table()
		: is_empty_{ true } {};

	Table(std::vector<std::string> fields, std::vector<std::vector<std::string>> rows)
		: fields_{ fields }, rows_{ rows }, is_empty_{ false } {
		for (int i = 0; i < fields.size(); i++) {
			field_to_index_map_.insert({ fields.at(i), i });
		}
	};

	Table(std::shared_ptr<ResWrapper>);

	int GetNumOfRows() { return rows_.size(); };

	int GetNumOfCols() { return fields_.size(); };

	std::vector<std::vector<std::string>> GetRows() {
		return rows_;
	}

	std::shared_ptr<Table> Join(std::shared_ptr<Table> that);

	bool IsEmpty() { return is_empty_; }

	bool ContainsSynonym(std::string synonym);

	bool ContainsSynonyms(std::vector<std::string> synonyms);
	

	std::shared_ptr<std::unordered_set<std::string>> GetDomainBySynonym(std::string synonym);

};