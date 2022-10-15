#include "CallRef.h"
#include "../DataRetriever.h"


std::string CallRef::GetAttrValue(DataRetriever& data_retriever, std::string& value) {
    return *data_retriever.MapCallsStmtNumToProcName(value);
}