#include "ReadRef.h"

#include "../DataRetriever.h"

std::string ReadRef::GetAttrValue(DataRetriever& data_retriever, std::string& value) {
    return *data_retriever.MapReadStmtNumToVarName(value);
}
