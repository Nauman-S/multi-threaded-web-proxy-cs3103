#include "ProgramNode.h"

using namespace std;

ProgramNode::ProgramNode() {
    this->children_ = {};
    this->proc_name_to_node_ = {};
}

std::vector<shared_ptr<ProcedureASTNode>> ProgramNode::GetChildren() const {
    return this->children_;
}

std::map<Procedure, std::shared_ptr<ProcedureASTNode>> ProgramNode::GetProcNodeMapping() const {
    return this->proc_name_to_node_;
}

void ProgramNode::AddProcedure(std::shared_ptr<ProcedureASTNode> proc) {
    this->children_.push_back(proc);
    this->proc_name_to_node_.insert(std::make_pair(proc->GetProc(), proc));
}

void ProgramNode::Extract(NodeExtractor& extractor) {
    extractor.ExtractProgramNode(*this);
}

string ProgramNode::Stringify() {
    string tp = "Program";
    string children_s = "";
    for (shared_ptr<ProcedureASTNode> node : children_) {
        children_s += node->Stringify();
    }
    return tp + children_s;
}