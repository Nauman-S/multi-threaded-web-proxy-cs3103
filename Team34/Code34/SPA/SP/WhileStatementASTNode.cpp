#include "WhileStatementASTNode.h"

using namespace std;

void WhileStatementASTNode::setChildren(std::vector<shared_ptr<StatementASTNode>>& c) {
	children = c;
}

std::vector<shared_ptr<StatementASTNode>> WhileStatementASTNode::getChildren() {
	return children;
}

void WhileStatementASTNode::setConditionExpression(std::shared_ptr<ConditionExpression> cond) {
	condition = cond;
}

shared_ptr<ConditionExpression> WhileStatementASTNode::getCondition() {
	return condition;
}

void WhileStatementASTNode::Extract(NodeExtractor& extractor) {

}

