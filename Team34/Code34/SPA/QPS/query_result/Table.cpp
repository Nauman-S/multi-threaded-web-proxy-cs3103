#include "Table.h"

#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_multimap;
using std::shared_ptr;


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

	for (string field : common_field) {
		hash_key += (GetValueInField(field, row) + ",");
	}

	return hash_key;
}

shared_ptr<Table> Table::Join(shared_ptr<Table> that) {
	vector<string> common_fields = GetCommonFields(that);

	if (common_fields.size() == 0) {
		return CrossProductJoin(that);
	}
	else {
		return HashJoin(that, common_fields);
	}
}

shared_ptr<Table> Table::CrossProductJoin(shared_ptr<Table> that) {
	vector<string> that_fields = that->fields_;

	vector<string> new_fields = that_fields;
	new_fields.insert(new_fields.end(), fields_.begin(), fields_.end());

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
	vector<string> that_fields = that->fields_;
	vector<string> new_fields = fields_;


	// remove the common fields to avoid duplicates
	// https://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
	for (string common_field : common_fields) {
		that_fields.erase(std::remove(that_fields.begin(), that_fields.end(), common_field), that_fields.end());
	}
	
	// new fields are in the sequence of (fields in this table + fields except common fields in that table )
	new_fields.insert(new_fields.end(), that_fields.begin(), that_fields.end());

	vector<vector<string>> new_rows;

	unordered_multimap<string, vector<string>> hashkey_to_rows;

	for (vector<string>& this_row : rows_) {
		string hashkey = ComputeHashkey(common_fields, this_row);
		hashkey_to_rows.insert({ hashkey, this_row });
	}

	for (vector<string>& that_row : that->rows_) {
		string hashkey = ComputeHashkey(common_fields, that_row);
		if (hashkey_to_rows.count(hashkey) == 0) continue;

		//https://stackoverflow.com/questions/9046922/unordered-multimap-iterating-the-result-of-find-yields-elements-with-differe
		auto hashkey_to_row_entries = hashkey_to_rows.equal_range(hashkey);

		for (auto hashkey_to_row_entry = hashkey_to_row_entries.first; hashkey_to_row_entry != hashkey_to_row_entries.second; ++hashkey_to_row_entry) {
			string hashkey = hashkey_to_row_entry->first;
			vector<string>& row = hashkey_to_row_entry->second;

			vector<string> new_row = row;
			

			for (int field_idx = 0; field_idx < that_row.size(); field_idx++) {
				string& that_field = that->GetFieldAtIndex(field_idx);
				if (std::find(common_fields.begin(), common_fields.end(), that_field) != common_fields.end()) {
					continue;
				}
				new_row.push_back(that_row.at(field_idx));
			}


			new_rows.push_back(new_row);
		}

	}

	return std::make_shared<Table>(new_fields, new_rows);
}

