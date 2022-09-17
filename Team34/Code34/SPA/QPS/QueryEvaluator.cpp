#include "QueryEvaluator.h"

#include <memory.h>

#include "Query.h"
#include "relation/Rel.h"
#include "ResultExtractor.h"


using std::vector;
using std::shared_ptr;


QueryEvaluator::QueryEvaluator(Query query) {
	query_ = query;
	query_result_ = QueryResult();
	data_retriever_ = DataRetriever();
};


bool QueryEvaluator::evaluate() {
	shared_ptr<vector<shared_ptr<Ref>>> select_tuple = query_.GetSelectTuple();
	for (shared_ptr<Ref> ref : *select_tuple) {
		//shared_ptr<ResWrapper> res_wrapper = data_retriever_.retrieve(std::make_shared<Ref>(ref));
		shared_ptr<ResWrapper> res_wrapper = data_retriever_.retrieve(ref);
		bool success = query_result_.MergeResult(res_wrapper);
		if (!success) {
			return false;
		}
	}

	shared_ptr<std::vector<shared_ptr<Rel>>> relations = query_.GetRelations();

	for (auto it = relations->begin(); it != relations->end(); ++it) {
		shared_ptr<Rel> relation = *it;
		// update sym_domain with data retriever

		shared_ptr<ResWrapper> res_wrapper = relation->GetMatch(data_retriever_);

		bool success = query_result_.MergeResult(res_wrapper);
		if (!success) {
			return false;
		}
		//data_retriever_.retrieve(*it);

	}
	return true;
}

vector<std::string> QueryEvaluator::ExtractResult() {
	ResultExtractor result_extractor = ResultExtractor(std::make_shared<QueryResult>(query_result_), query_.GetSelectTuple());
	return result_extractor.GetFormattedResult();
}


	
