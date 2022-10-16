#include "NextExtractor.h"

#include "../ast/ProgramNode.h"
#include "../ast/ProcedureASTNode.h"

#include "../ast/AssignStatementASTNode.h"
#include "../ast/CallStatementASTNode.h"
#include "../ast/PrintStatementASTNode.h"
#include "../ast/ReadStatementASTNode.h"
#include "../ast/ConditionExpression.h"

#include "../ast/IfStatementASTNode.h"
#include "../ast/WhileStatementASTNode.h"

NextExtractor::NextExtractor(std::shared_ptr<WritePKBManager> manager): NodeExtractor(manager) {}

void NextExtractor::ExtractProgramNode(const ProgramNode& program) {
	std::vector<shared_ptr<ProcedureASTNode>> procedures = program.GetChildren();
	for (shared_ptr<ProcedureASTNode> proc : procedures) {
		proc->Extract(*this);
		// Clear stored statements and blocks from last extracted procedure
		this->ClearPrevStmts(); 
		this->ClearPrevBlocks();
	}
}

void NextExtractor::ExtractProcedureNode(const ProcedureASTNode& proc) {
	std::vector<std::shared_ptr<StatementASTNode>> stmts = proc.GetChildren();
	for (std::shared_ptr<StatementASTNode> stmt : stmts) {
		stmt->Extract(*this);
	}
	this->CreateBlock(); // Store last statements of procedure with implicit end block
	this->MarkBlockEnd();
}

void NextExtractor::ExtractAssignmentNode(const AssignStatementASTNode& assign) {
	StmtNum line = assign.GetLineIndex();
	this->SetDirectEdge(line);
	this->SetBlockEdge(line);
}

void NextExtractor::ExtractCallNode(const CallStatementASTNode& call) {
	StmtNum line = call.GetLineIndex();
	this->SetDirectEdge(line);
	this->SetBlockEdge(line);
}

void NextExtractor::ExtractPrintNode(const PrintStatementASTNode& print) {
	StmtNum line = print.GetLineIndex();
	this->SetDirectEdge(line);
	this->SetBlockEdge(line);
}

void NextExtractor::ExtractReadNode(const ReadStatementASTNode& read) {
	StmtNum line = read.GetLineIndex();
	this->SetDirectEdge(line);
	this->SetBlockEdge(line);
}

void NextExtractor::ExtractIfNode(const IfStatementASTNode& if_stmt) {
	StmtNum parent_line = if_stmt.GetLineIndex();
	this->SetDirectEdge(parent_line);
	this->CreateBlock(); // Create block for preceeding statements
	this->MarkBlockEnd();

	this->SetBlockEdge(parent_line);
	this->CreateBlock(); // Create single statement block for current if statement
	this->MarkBlockEnd();

	std::vector<std::shared_ptr<StatementASTNode>> then_children = if_stmt.GetIfChildren();
	for (std::shared_ptr<StatementASTNode> then_child : then_children) {
		then_child->Extract(*this);
	}
	std::set<StmtNum> prev_from_if_branch = this->prev_stmts_;
	std::set<StmtNum> blocks_from_if_branch = this->prev_blocks_;

	this->ClearPrevStmts();
	this->AddPrevStmt(parent_line);

	this->CreateBlock(); // Create block for if children
	// Reset block information to parent for else children
	this->block_start_stmt_ = parent_line;
	this->block_end_stmt_ = parent_line;
	this->ClearPrevBlocks();
	this->AddPrevBlockStart(parent_line);
	this->MarkBlockEnd();

	std::vector<std::shared_ptr<StatementASTNode>> else_children = if_stmt.GetElseChildren();
	for (std::shared_ptr<StatementASTNode> else_child : else_children) {
		else_child->Extract(*this);
	}
	std::set<StmtNum> prev_from_else_branch = this->prev_stmts_;
	std::set<StmtNum> blocks_from_else_branch = this->prev_blocks_;

	this->CreateBlock(); // Create block for else children

	// Combine statement numbers from both if and else branches, as both will
	// be previous to the statement right after this if statement
	this->ClearPrevStmts();
	for (StmtNum num : prev_from_if_branch) {
		this->AddPrevStmt(num);
	}
	for (StmtNum num : prev_from_else_branch) {
		this->AddPrevStmt(num);
	}

	this->ClearPrevBlocks();
	for (StmtNum num : blocks_from_if_branch) {
		this->AddPrevBlockStart(num);
	}
	for (StmtNum num : blocks_from_else_branch) {
		this->AddPrevBlockStart(num);
	}
	this->MarkBlockEnd();
}

void NextExtractor::ExtractWhileNode(const WhileStatementASTNode& while_stmt) {
	StmtNum parent_line = while_stmt.GetLineIndex();
	this->SetDirectEdge(parent_line);
	
	this->CreateBlock(); // Create block for preceeding statements
	this->MarkBlockEnd();

	this->SetBlockEdge(parent_line);
	this->CreateBlock(); // Create single statement block for current while statement
	this->MarkBlockEnd();

	std::vector<std::shared_ptr<StatementASTNode>> children = while_stmt.GetChildren();
	for (std::shared_ptr<StatementASTNode> child : children) {
		child->Extract(*this);
	}

	// Set direct next from last statement(s) of while children
	this->SetDirectEdge(parent_line);
	
	this->CreateBlock();
	this->MarkBlockEnd();
	this->SetBlockEdge(parent_line);
	this->MarkBlockEnd();
}

void NextExtractor::ExtractConditionExpression(const ConditionExpression& cond) {}

void NextExtractor::SetDirectEdge(StmtNum line) {
	this->AddNextRelation(line);
	this->ClearPrevStmts();
	this->AddPrevStmt(line);
}

void NextExtractor::SetBlockEdge(StmtNum line) {
	if (!this->is_block_end_) {
		// Extend the existing block
		this->block_end_stmt_ = line;
		return;
	}

	for (StmtNum block_start : this->prev_blocks_) {
		this->write_manager_->SetOptimisedCFGEdge(block_start, line);
	}
	this->block_start_stmt_ = line;
	this->block_end_stmt_ = line;
	this->ClearPrevBlocks();
	this->AddPrevBlockStart(line);
	this->is_block_end_ = false;
}

void NextExtractor::AddPrevStmt(StmtNum num) {
	this->prev_stmts_.insert(num);
}

void NextExtractor::ClearPrevStmts() {
	this->prev_stmts_.clear();
}

void NextExtractor::AddPrevBlockStart(StmtNum block_start) {
	this->prev_blocks_.insert(block_start);
}

void NextExtractor::ClearPrevBlocks() {
	this->prev_blocks_.clear();
}

void NextExtractor::CreateBlock() {
	this->write_manager_->SetCodeBlock(this->block_start_stmt_, this->block_end_stmt_);
}

void NextExtractor::MarkBlockEnd() {
	this->is_block_end_ = true;
}

// Populate Next relationship from set of previous statements
void NextExtractor::AddNextRelation(StmtNum current) {
	for (StmtNum prev : this->prev_stmts_) {
		this->write_manager_->SetNext(prev, current);
	}
}

