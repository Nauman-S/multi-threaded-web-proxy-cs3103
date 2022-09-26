#include "Table.h"

#include <iterator>

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

string Table::ComputeHashkey(vector<string> common_field, unordered_map<string, string> row) {
	string hash_key = "";

	for (string field : common_field) {
		hash_key += row.at(field);
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

	vector<unordered_map<string, string>> new_rows; 

	
	for (unordered_map<string, string> this_row: rows_) {
		for (unordered_map<string, string> that_row : that->rows_) {
			unordered_map<string, string> new_row = this_row;
			new_row.insert(that_row.begin(), that_row.end());
			new_rows.push_back(new_row);
		}
	}

	return std::make_shared<Table>(new_fields, new_rows);
}

shared_ptr<Table> Table::HashJoin(shared_ptr<Table> that, vector<string> common_fields) {
	vector<string> that_fields = that->fields_;
	vector<string> new_fields = that_fields;


	// remove the common fields to avoid duplicates
	// https://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
	for (string common_field : common_fields) {
		new_fields.erase(std::remove(new_fields.begin(), new_fields.end(), common_field), new_fields.end());
	}
	
	new_fields.insert(new_fields.end(), fields_.begin(), fields_.end());

	vector<unordered_map<string, string>> new_rows;

	unordered_multimap<string, unordered_map<string, string>> hashkey_to_rows;

	for (unordered_map<string, string> this_row : rows_) {
		string hashkey = ComputeHashkey(common_fields, this_row);
		hashkey_to_rows.insert({ hashkey, this_row });
	}

	for (unordered_map<string, string> that_row : that->rows_) {
		string hashkey = ComputeHashkey(common_fields, that_row);
		if (hashkey_to_rows.count(hashkey) == 0) continue;

		//https://stackoverflow.com/questions/9046922/unordered-multimap-iterating-the-result-of-find-yields-elements-with-differe
		auto iterators = hashkey_to_rows.equal_range(hashkey);

		for (auto iterator = iterators.first; iterator != iterators.second; ++iterator) {
			string hashkey = iterator->first;
			unordered_map<string, string> row = iterator->second;

			unordered_map<string, string> new_row = that_row;
			new_row.insert(row.begin(), row.end());

			new_rows.push_back(new_row);
		}

	}

	return std::make_shared<Table>(new_fields, new_rows);
}

