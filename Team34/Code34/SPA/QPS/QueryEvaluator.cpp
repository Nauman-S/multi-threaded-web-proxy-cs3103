#include "QueryEvaluator.h"

#include <memory.h>

#include "Query.h"
#include "relation/Rel.h"
#include "ResultExtractor.h"
#include "query_result/Table.h"


using std::vector;
using std::shared_ptr;


QueryEvaluator::QueryEvaluator(Query query) {
	query_ = query;
	query_result_ = QueryResult();
	data_retriever_ = DataRetriever();
};


bool QueryEvaluator::Evaluate() {
	shared_ptr<vector<shared_ptr<Ref>>> select_tuple = query_.GetSelectTuple();
	for (shared_ptr<Ref> ref : *select_tuple) {
		//shared_ptr<ResWrapper> res_wrapper = data_retriever_.retrieve(std::make_shared<Ref>(ref));
		shared_ptr<ResWrapper> res_wrapper = data_retriever_.retrieve(ref);
		bool success = query_result_.MergeResult(res_wrapper);
		if (!success) {
			return false;
		}
	}

	std::vector<shared_ptr<Clause>> clauses;

	shared_ptr<std::vector<shared_ptr<Rel>>> relations = query_.GetRelations();
	shared_ptr<std::vector<shared_ptr<Pattern>>> patterns = query_.GetPatterns();
	shared_ptr<std::vector<shared_ptr<With>>> with_clauses = query_.GetWithClauses();

	clauses.insert(clauses.end(), relations->begin(), relations->end());
	clauses.insert(clauses.end(), patterns->begin(), patterns->end());
	clauses.insert(clauses.end(), with_clauses->begin(), with_clauses->end());

	//for (auto it = relations->begin(); it != relations->end(); ++it) {
	//	shared_ptr<Rel> relation = *it;
	//	// update sym_domain with data retriever

	//	shared_ptr<ResWrapper> res_wrapper = relation->GetMatch(data_retriever_);

	//	bool success = query_result_.MergeResult(res_wrapper);
	//	if (!success) {
	//		return false;
	//	}
	//	//data_retriever_.retrieve(*it);
	//}

	//
	//for (auto it = patterns->begin(); it != patterns->end(); ++it) {
	//	shared_ptr<Pattern> pattern = *it;

	//	shared_ptr<ResWrapper> res_wrapper = pattern->GetMatch(data_retriever_);

	//	bool success = query_result_.MergeResult(res_wrapper);
	//	if (!success) {
	//		return false;
	//	}
	//	//data_retriever_.retrieve(*it);

	//}
	bool success = EvaluateGroup(clauses);

	return success;
}

bool QueryEvaluator::EvaluateGroup(vector<shared_ptr<Clause>> clauses) {
	Table table;

	for (shared_ptr<Clause> clause : clauses) {
		shared_ptr<ResWrapper> res_wrapper = clause->GetMatch(data_retriever_);
		if (res_wrapper->GetResType() == ResType::kBool) {
			if (res_wrapper->IsValid()) {
				continue;
			}
			else {
				return false;
			}	
		}

		//table = table.Join(res_wrapper);
	}

}

vector<std::string> QueryEvaluator::ExtractResult() {
	ResultExtractor result_extractor = ResultExtractor(std::make_shared<QueryResult>(query_result_), query_.GetSelectTuple());

	return result_extractor.GetFormattedResult();
}


	
