#include "PrintRef.h"
#include "../DataRetriever.h"

std::string PrintRef::GetAttrValue(DataRetriever& data_retriever, std::string& value) {
    return *data_retriever.MapPrintStmtNumToVarName(value);
}