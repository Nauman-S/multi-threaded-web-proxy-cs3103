#include "ReadStatementASTNode.h"

#include <iostream>

using namespace std;

void ReadStatementASTNode::SetVariable(Variable& v) {
    var = v;
}

Variable ReadStatementASTNode::GetReadVariable() const {
    return var;
}

void ReadStatementASTNode::Extract(NodeExtractor& extractor) {
    extractor.ExtractReadNode(*this);
}

string ReadStatementASTNode::Stringify() {
    string tp = "Read";
    string var_s = var;
    return tp + var_s;
}