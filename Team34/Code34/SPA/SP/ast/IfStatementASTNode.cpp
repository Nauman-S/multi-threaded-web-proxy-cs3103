#include "IfStatementASTNode.h"

using namespace std;

void IfStatementASTNode::SetIfChildren(std::vector<std::shared_ptr<StatementASTNode>>& if_c) {
	ifChildren = if_c;
}

std::vector<std::shared_ptr<StatementASTNode>>IfStatementASTNode::GetIfChildren() {
	return ifChildren;
}

void IfStatementASTNode::SetElseChildren(std::vector<std::shared_ptr<StatementASTNode>>& else_c) {
	elseChildren = else_c;
}

std::vector<std::shared_ptr<StatementASTNode>> IfStatementASTNode::GetElseChildren() {
	return elseChildren;
}

void IfStatementASTNode::SetConditionExpression(shared_ptr<ConditionExpression> cond) {
	condition = cond;
}

shared_ptr<ConditionExpression> IfStatementASTNode::GetCondition() {
	return condition;
}

void IfStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractIfNode(*this);
}
