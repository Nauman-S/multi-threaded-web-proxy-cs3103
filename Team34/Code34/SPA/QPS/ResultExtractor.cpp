#include "ResultExtractor.h"

#include <assert.h>

string ResultExtractor::GetFormattedResult() {

	// assert the number of syns in tuple > 0;
	assert(select_tuple_->size() > 0 && "Size of tuple must be greater than 0");

	if (select_tuple_->size() == 1) {
		return GetSingleSynResult();
	}
	else {
		return GetMultiSynResult();
	}
}

string ResultExtractor::GetSingleSynResult() {
	Ref& ref = select_tuple_->at(0);

	return "";

}

string ResultExtractor::GetMultiSynResult() {
	return "GetMultiSynResult() is Not Implemented Yet";
}