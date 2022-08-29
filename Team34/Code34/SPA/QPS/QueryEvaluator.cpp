#include "QueryEvaluator.h"
#include "Query.h"
#include "relation/Rel.h"


QueryEvaluator::QueryEvaluator(Query query) {
	query_ = query;
};

bool QueryEvaluator::evaluate() {
	for (Rel& rel : query_.GetRelations()) {
		
		// update sym_domain with data retriever
		//data_retriever_.retrieve(rel, syn_domains);

	}
}