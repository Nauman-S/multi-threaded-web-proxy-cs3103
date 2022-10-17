#include "AssignStatementASTNode.h"

using namespace std;

void AssignStatementASTNode::SetLeft(Variable& l) {
    left = l;
}

void AssignStatementASTNode::SetRightVars(std::vector<Variable>& r) {
    right_vars = r;
}

void AssignStatementASTNode::SetRightCons(std::vector<Constant>& r) {
    right_cons = r;
}

Variable AssignStatementASTNode::GetLeft() const {
    return left;
}

std::vector<Variable> AssignStatementASTNode::GetRightVars() const {
    return right_vars;
}

std::vector<Constant> AssignStatementASTNode::GetRightCons() const {
    return right_cons;
}

void AssignStatementASTNode::SetInfix(string& s) {
    infix = s;
}

string AssignStatementASTNode::GetInfix() const {
    return infix;
}

void AssignStatementASTNode::Extract(NodeExtractor& extractor) {
    extractor.ExtractAssignmentNode(*this);
}

string AssignStatementASTNode::Stringify() {
    string tp = "Assign";
    string left_s = left;
    string right_cons_s = "";
    string right_vars_s = "";
    string infix_s = infix;
    for (Constant con : right_cons) {
        right_cons_s += to_string(con);
    }
    for (Variable var : right_vars) {
        right_vars_s += var;
    }
    return tp + left_s + left_s + right_cons_s + right_vars_s;
}