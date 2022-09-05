# include "IfStatementASTNode.h"

using namespace std;

void IfStatementASTNode::setIfChildren(std::vector<std::shared_ptr<StatementASTNode>>& if_c) {
	ifChildren = if_c;
}

std::vector<std::shared_ptr<StatementASTNode>>IfStatementASTNode::getIfChildren() {
	return ifChildren;
}

void IfStatementASTNode::setElseChildren(std::vector<std::shared_ptr<StatementASTNode>>& else_c) {
	elseChildren = else_c;
}

std::vector<std::shared_ptr<StatementASTNode>> IfStatementASTNode::getElseChildren() {
	return elseChildren;
}

void IfStatementASTNode::setConditionExpression(shared_ptr<ConditionExpression> cond) {
	condition = cond;
}

shared_ptr<ConditionExpression> IfStatementASTNode::getCondition() {
	return condition;
}

void IfStatementASTNode::Extract(NodeExtractor& extractor) {

}

