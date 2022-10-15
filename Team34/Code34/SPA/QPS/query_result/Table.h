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

	std::unordered_map<std::string, int> field_to_index_map_;

	std::vector<std::vector<std::string>> rows_;

	
	std::string GetFieldAtIndex(unsigned idx) {
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

protected:
	bool is_empty_;

public:
	Table()
		: is_empty_{ false } {};

	Table(std::vector<std::string> fields, std::vector<std::vector<std::string>> rows)
		: fields_{ fields }, rows_{ rows }  {
		for (unsigned i = 0; i < fields.size(); i++) {
			field_to_index_map_.insert({ fields.at(i), i });
		}
		is_empty_ = (rows_.size() == 0);
	};

	Table(std::shared_ptr<ResWrapper>);

	int GetNumOfRows() { return rows_.size(); };
	unsigned GetNumOfCols() { return fields_.size(); };

	std::vector<std::vector<std::string>> GetRows() {
		return rows_;
	}

	virtual std::shared_ptr<Table> Join(std::shared_ptr<Table> that);

	virtual bool IsEmpty() { return GetNumOfRows() == 0; }

	virtual bool IsWildcard() { return false; }

	bool ContainsSynonym(std::string synonym);

	bool ContainsSynonyms(std::vector<std::string> synonyms);

	std::shared_ptr<std::unordered_set<std::string>> GetDomainBySynonym(std::string synonym);

	std::shared_ptr<std::unordered_set<std::string>> GetDomainBySynonyms(std::vector<std::string> synonyms);

	std::shared_ptr<std::vector<std::vector<std::string>>> ExtractSynonyms(std::vector<std::string> synonyms);

};