#include "WhileStatementASTNode.h"

using namespace std;

void WhileStatementASTNode::SetChildren(std::vector<shared_ptr<StatementASTNode>>& c) {
	children = c;
}

std::vector<shared_ptr<StatementASTNode>> WhileStatementASTNode::GetChildren() const {
	return children;
}

void WhileStatementASTNode::SetConditionExpression(std::shared_ptr<ConditionExpression> cond) {
	condition = cond;
}

shared_ptr<ConditionExpression> WhileStatementASTNode::GetCondition() const {
	return condition;
}

void WhileStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractWhileNode(*this);
}
