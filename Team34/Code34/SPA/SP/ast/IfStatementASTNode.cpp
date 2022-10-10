#include "IfStatementASTNode.h"

using namespace std;

void IfStatementASTNode::SetIfChildren(std::vector<std::shared_ptr<StatementASTNode>>& if_c) {
	ifChildren = if_c;
}

std::vector<std::shared_ptr<StatementASTNode>>IfStatementASTNode::GetIfChildren() const {
	return ifChildren;
}

void IfStatementASTNode::SetElseChildren(std::vector<std::shared_ptr<StatementASTNode>>& else_c) {
	elseChildren = else_c;
}

std::vector<std::shared_ptr<StatementASTNode>> IfStatementASTNode::GetElseChildren() const {
	return elseChildren;
}

void IfStatementASTNode::SetConditionExpression(shared_ptr<ConditionExpression> cond) {
	condition = cond;
}

shared_ptr<ConditionExpression> IfStatementASTNode::GetCondition() const {
	return condition;
}

void IfStatementASTNode::Extract(NodeExtractor& extractor) {
	extractor.ExtractIfNode(*this);
}

string IfStatementASTNode::Stringify() {
	string tp = "if";
	string if_s = "";
	string else_s = "";
	string condition_s = condition->Stringify();
	for (shared_ptr<StatementASTNode> node : ifChildren) {
		if_s += node->Stringify()
	}
	for (shared_ptr<StatementASTNode> node : elseChildren) {
		else_s += node->Stringify()
	}
	return tp + condition_s + if_s + else_s;
}