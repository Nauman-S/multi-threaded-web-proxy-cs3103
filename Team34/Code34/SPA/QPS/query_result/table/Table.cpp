#include "Table.h"

#include <iterator>
#include <algorithm>

#include "../ResWrapper.h"
#include "../TableRes.h"
#include "../SetRes.h"
#include "EmptyTable.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_multimap;
using std::shared_ptr;


Table::Table(shared_ptr<SetRes> set_res) {
	fields_.push_back(set_res->GetSyn());
	for (const auto& value : *set_res->GetDomain()) {
		rows_.push_back({ value });
	}
	SetFieldToIndexMap(fields_);
}

Table::Table(shared_ptr<TableRes> table_res) {
	fields_ = *table_res->Columns();	
	for (auto& row : *table_res->GetRows()) {
		rows_.push_back({ row.first, row.second });
	}
	SetFieldToIndexMap(fields_);
}

vector<string> Table::GetCommonFields(shared_ptr<Table> that) {
	vector<string> common_fields;
	vector<string> that_fields = that->fields_;
	for (string this_field : fields_) {
		if (std::find(that_fields.begin(), that_fields.end(), this_field) != that_fields.end()) {
			common_fields.push_back(this_field);
		}
	}
	return common_fields;
}

string Table::ComputeHashkey(vector<string> common_field, vector<string> row) {
	string hash_key = "";
	string delimiter = ",";

	for (string field : common_field) {
		hash_key += (GetValueInField(field, row) + delimiter);
	}

	return hash_key;
}

shared_ptr<Table> Table::Join(shared_ptr<Table> that) {
	if (that->IsWildcard()) return shared_ptr<Table>(this);

	vector<string> common_fields = GetCommonFields(that);

	if (common_fields.size() == 0) {
		return CrossProductJoin(that);
	} else {
		return HashJoin(that, common_fields);
	}
}


shared_ptr<Table> Table::CrossProductJoin(shared_ptr<Table> that) {
	vector<string> that_fields = that->fields_;
	vector<string> new_fields = fields_;
	new_fields.insert(new_fields.end(), that_fields.begin(), that_fields.end());

	vector<vector<string>> new_rows; 

	for (vector<string>& this_row: rows_) {
		for (vector<string>& that_row : that->rows_) {
			vector<string> new_row = this_row;
			new_row.insert(new_row.end(), that_row.begin(), that_row.end());
			new_rows.push_back(new_row);
		}
	}

	return std::make_shared<Table>(new_fields, new_rows);
}


shared_ptr<Table> Table::HashJoin(shared_ptr<Table> that, vector<string> common_fields) {
	vector<string> new_fields = fields_;

	// remove the common fields to avoid duplicates
	vector<string> that_fields_except_common = that->fields_;
	for (string common_field : common_fields) {
		that_fields_except_common.erase(std::remove(that_fields_except_common.begin(), that_fields_except_common.end(), common_field), that_fields_except_common.end());
	}
	
	// new fields are in the sequence of (fields in this table + fields except common fields in that table)
	new_fields.insert(new_fields.end(), that_fields_except_common.begin(), that_fields_except_common.end());

	
	unordered_multimap<string, vector<string>> hashkey_to_row_map;
	for (vector<string>& this_row : rows_) {
		string hashkey = ComputeHashkey(common_fields, this_row);
		hashkey_to_row_map.insert({ hashkey, this_row });
	}


	vector<vector<string>> new_rows;
	for (vector<string>& that_row : that->rows_) {
		vector<string>& that_row_wo_common_field = GetRowWithoutCommonField(that, that_row, common_fields);
		string hashkey = that->ComputeHashkey(common_fields, that_row);

        auto& matched_row_entries = hashkey_to_row_map.equal_range(hashkey);
        for (auto& matched_row_entry = matched_row_entries.first; matched_row_entry != matched_row_entries.second; ++matched_row_entry) {
            vector<string> matched_row = matched_row_entry->second;
			matched_row.insert(matched_row.end(), that_row_wo_common_field.begin(), that_row_wo_common_field.end());
            new_rows.push_back(matched_row);
        }
	}

	if (new_rows.size() == 0) {
		return std::make_shared<EmptyTable>();
	}

	return std::make_shared<Table>(new_fields, new_rows);
}

vector<string> Table::GetRowWithoutCommonField(shared_ptr<Table> that, const vector<string>& that_row, const vector<string>& common_fields) {
	vector<string> that_row_wo_common_field;

	size_t that_col_nums = that->GetNumOfCols();
	for (size_t field_idx = 0; field_idx < that_col_nums; field_idx++) {
		string& that_field = that->GetFieldAtIndex(field_idx);
		if (std::find(common_fields.begin(), common_fields.end(), that_field) == common_fields.end()) {
			that_row_wo_common_field.push_back(that_row.at(field_idx));
		}
	}

	return that_row_wo_common_field;
}

bool Table::HasSynonym(string synonym) {
	return std::find(fields_.begin(), fields_.end(), synonym) != fields_.end();
}

shared_ptr<vector<vector<string>>> Table::ExtractSynonyms(std::vector<std::string> synonyms) {
	shared_ptr<vector<vector<string>>> result_rows = std::make_shared<vector<vector<string>>>();
	for (auto& row : rows_) {
		vector<string> curr_row;
		for (string& synonym : synonyms) {
			int index = field_to_index_map_.at(synonym);
			curr_row.push_back(row.at(index));
		}
	
		result_rows->push_back(curr_row);
	}
	return result_rows;
}

