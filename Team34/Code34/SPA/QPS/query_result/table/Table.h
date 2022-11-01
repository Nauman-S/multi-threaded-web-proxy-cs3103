#pragma once

#include <assert.h>

#include <unordered_set>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "../ResWrapper.h"

class Table {
private:
	std::vector<std::string> fields_;

	std::unordered_map<std::string, int> field_to_index_map_;

	std::vector<std::vector<std::string>> rows_;

	void SetFieldToIndexMap(const std::vector<std::string>& fields) {
		for (size_t i = 0; i < fields.size(); i++) {
			field_to_index_map_.insert({ fields.at(i), i });
		}
	}

	std::string GetFieldAtIndex(unsigned idx) {
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

	std::vector<std::string> GetRowWithoutCommonField(std::shared_ptr<Table> that, const std::vector<std::string>& that_row, const std::vector<std::string>& common_fields);

public:
	Table() {}

	Table(std::vector<std::string> fields, std::vector<std::vector<std::string>> rows)
		: fields_{ fields }, rows_{ rows }  {
		SetFieldToIndexMap(fields_);
	}

	explicit Table(std::shared_ptr<SetRes>);
	explicit Table(std::shared_ptr<TableRes>);

	int GetNumOfRows() { return rows_.size(); }
	unsigned GetNumOfCols() { return fields_.size(); }

	std::vector<std::vector<std::string>> GetRows() {
		return rows_;
	}

	virtual std::shared_ptr<Table> Join(std::shared_ptr<Table> that);

	virtual bool IsEmpty() { return GetNumOfRows() == 0; }

	virtual bool IsWildcard() { return false; }

	bool HasSynonym(std::string synonym);

	std::shared_ptr<std::unordered_set<std::string>> GetDomainBySynonym(std::string synonym);

	std::shared_ptr<std::unordered_set<std::string>> GetDomainBySynonyms(std::vector<std::string> synonyms);

	std::shared_ptr<std::vector<std::vector<std::string>>> ExtractSynonyms(std::vector<std::string> synonyms);

};