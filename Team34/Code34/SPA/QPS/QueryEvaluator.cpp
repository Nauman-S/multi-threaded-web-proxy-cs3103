#include "QueryEvaluator.h"
#include "Query.h"
#include "relation/Rel.h"


QueryEvaluator::QueryEvaluator(Query query) {
	query_ = query;
};

bool QueryEvaluator::evaluate() {
	std::shared_ptr<std::vector<Rel>> relations = query_.GetRelations();

	for (auto it = relations->begin(); it != relations->end(); ++it) {
		
		// update sym_domain with data retriever
		//data_retriever_.retrieve(rel, syn_domains);

	}

	return false;
}