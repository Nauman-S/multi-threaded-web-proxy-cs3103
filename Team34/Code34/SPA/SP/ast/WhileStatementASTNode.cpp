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

string WhileStatementASTNode::Stringify() {
	string tp = "While";
	string condition_s = condition->Stringify();
	string children_s = "";
	for (shared_ptr<StatementASTNode> node : children) {
		children_s += node->Stringify();
	}
	return tp + condition_s + children_s;
}