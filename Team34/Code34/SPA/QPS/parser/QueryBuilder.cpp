#include "QueryBuilder.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <memory>

#include "SyntaxError.h"
#include "SemanticError.h"
#include "..\..\Utils\InvalidTokenException.h"
#include "..\reference\ValType.h"
#include "..\reference\Ref.h"
#include "..\reference\StmtRef.h"
#include "..\reference\ReadRef.h"
#include "..\reference\PrintRef.h"
#include "..\reference\CallRef.h"
#include "..\reference\WhileRef.h"
#include "..\reference\IfRef.h"
#include "..\reference\AssignRef.h"
#include "..\reference\VarRef.h"
#include "..\reference\ConstRef.h"
#include "..\reference\ConstRef.h"
#include "..\reference\ProcRef.h"
#include "..\relation\Rel.h"
#include "..\relation\FollowsRel.h"
#include "..\relation\FollowsTRel.h"
#include "..\relation\ParentRel.h"
#include "..\relation\ParentTRel.h"
#include "..\relation\UsesSRel.h"
#include "..\relation\UsesPRel.h"

using std::shared_ptr;


QueryBuilder::QueryBuilder() {
	lexer_ = std::make_shared<QueryLexer>();
}

shared_ptr<Query> QueryBuilder::GetQuery(const std::string& query_string_) {
		this->lexer_->FeedQuery(query_string_);
		
		synonyms_ = ParseDeclarationStatements();
		
		shared_ptr<Query> query_ = ParseSelectStatement();
		std::shared_ptr<Query> sp_ = std::shared_ptr<Query>(query_);
		return sp_;
}

std::vector<shared_ptr<Ref>> QueryBuilder::ParseDeclarationStatements() {
	std::vector<shared_ptr<Ref>> synonyms;
	shared_ptr<Ref> synonym_;

	while (this->lexer_->HasDesignEntity()) {
		synonym_ = ParseDeclarationStatement();
		synonyms.push_back(synonym_);
	}

	return synonyms;
}



shared_ptr<Ref> QueryBuilder::ParseDeclarationStatement() {
	std::string design_entity_ = this->lexer_->MatchDesignEntityKeyword();

	if (this->lexer_->HasIdentity()) {
		std::string synonym_ = this->lexer_->MatchIdentity();

		if (this->lexer_->HasEndOfDeclarationStatement()) {
			this->lexer_->MatchEndOfDeclarationStatement();
			shared_ptr<Ref> ref_ = CreateReference(design_entity_, synonym_);
			return ref_;
		}
		else {
			throw SyntaxError("Declaration Statement - Missing semicolon (;) at end of statement");
		}
	}
	else {
		throw SyntaxError("Declaration Statement - Missing Synonym");
	}

}

// this should be inside Create Ref class based on factory pattern. for now its here
shared_ptr<Ref> QueryBuilder::CreateReference(std::string design_entity_, std::string synonym_) {
	if (design_entity_.compare("STMT") == 0) {
		return shared_ptr<StmtRef>(new StmtRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("READ") == 0) {
		return shared_ptr<ReadRef>(new ReadRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("PRINT") == 0) {
		return shared_ptr<PrintRef>(new PrintRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("CALL") == 0) {
		return shared_ptr<CallRef>(new CallRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("WHILE") == 0) {
		return shared_ptr<WhileRef>(new WhileRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("IF") == 0) {
		return shared_ptr<IfRef>(new IfRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("ASSIGN") == 0) {
		return shared_ptr<AssignRef>(new AssignRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("VARIABLE") == 0) {
		return shared_ptr<VarRef>(new VarRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("CONSTANT") == 0) {
		return shared_ptr<ConstRef>(new ConstRef(ValType::kSynonym, synonym_));
	}
	else if (design_entity_.compare("PROCEDURE") == 0) {
		return shared_ptr<ProcRef>(new ProcRef(ValType::kSynonym, synonym_));
	}
	else {
		throw new SyntaxError("This error should never be called - Iconsistent Naming OF design_entities");
	}

}

shared_ptr<Query> QueryBuilder::ParseSelectStatement() {

	if (this->lexer_->HasKeyword("SELECT")) {
		this->lexer_->MatchKeyword("SELECT");
		std::vector<shared_ptr<Ref>> select_tuple_ = ParseReturnValues();
		std::vector<shared_ptr<Rel>> relations_ = ParseRelations();
		std::vector<shared_ptr<Pattern>> patterns_ = ParsePatterns();

		if (this->lexer_->HasMoreTokens()) {
			throw SyntaxError("Unexpected token at end of query");
		}

		std::shared_ptr<std::vector<std::shared_ptr<Ref>>> select_tuple_s_ = std::make_shared<std::vector<std::shared_ptr<Ref>>>();
		for (shared_ptr<Ref> ref_ : select_tuple_) {
			std::shared_ptr <Ref> ref_s_ = std::shared_ptr<Ref>(ref_);
			select_tuple_s_->push_back(ref_s_);
		}

		std::shared_ptr <std::vector<std::shared_ptr<Rel>>> relations_s_ = std::make_shared<std::vector<std::shared_ptr<Rel>>>();
		for (shared_ptr<Rel> rel_ : relations_) {
			std::shared_ptr <Rel> rel_s_ = std::shared_ptr<Rel>(rel_);
			relations_s_->push_back(rel_s_);
		}

		std::shared_ptr < std::vector<std::shared_ptr<Pattern>>> patterns_s_ = std::make_shared<std::vector<std::shared_ptr<Pattern>>>();
		for (shared_ptr<Pattern> pattern_ : patterns_) {
			std::shared_ptr <Pattern> pattern_s_ = std::shared_ptr<Pattern>(pattern_);
			patterns_s_->push_back(pattern_s_);
		}

		shared_ptr<Query> query = shared_ptr<Query>(new Query(select_tuple_s_, relations_s_, patterns_s_));
		return query;
	}
	else {
		throw SyntaxError("Select Statment - Missing (select) keyword");
	}
}

std::vector<shared_ptr<Ref>> QueryBuilder::ParseReturnValues() {
	std::vector<shared_ptr<Ref>> select_tuple_;

	if (this->lexer_->HasIdentity()) {
		std::string identity_ = this->lexer_->MatchIdentity();

		for (shared_ptr<Ref> ref : synonyms_) {
			if (ref->GetName().compare(identity_) == 0) {
				select_tuple_.push_back(ref);
			}
		}

		if (select_tuple_.size() == 1) {
			return select_tuple_;
		}
		else {
			throw SyntaxError("Select Statement - Synonym " + identity_ + " used without declaration first");
		}

	}
	else {
		throw SyntaxError("Select Statement - Missing synonyms to be returned");
	}
}

bool QueryBuilder::HasSuchThatClause() {

	if (this->lexer_->HasKeyword("SUCH")) {
		this->lexer_->MatchKeyword("SUCH");
		if (this->lexer_->HasKeyword("THAT")) {
			this->lexer_->MatchKeyword("THAT");
			return true;
		}
	}

	return false;
}


//Continue from here
std::vector <shared_ptr<Rel>> QueryBuilder::ParseRelations() {
	shared_ptr<Rel> rel_ref_clause_;
	if (!HasSuchThatClause()) {
		return relations_;
	}
	std::string relation_name;

	relation_name = lexer_->MatchReferenceKeyword();

	lexer_->MatchOpeningBrace();
	
	//if (relation_name == "USES") {
	//	rel_ref_clause_ = ParseUseRel();
	//}
	rel_ref_clause_ = ParseRelRefClause(relation_name);

	lexer_->MatchClosingBrace();

	relations_.push_back(rel_ref_clause_);

	return relations_;
}

shared_ptr<Rel> QueryBuilder::ParseRelRefClause(std::string relation_name) {
	std::set <std::string> stmt_ref_ = { "FOLLOWS", "FOLLOWS*", "PARENT", "PARENT*"};


	if (stmt_ref_.find(relation_name) != stmt_ref_.end()) {
		throw SyntaxError("FOLLOWS, FOLLOWS*, PARENT, PARENT* have not yet been implemented");
	}
	else if (relation_name == "USES") {
		return ParseUsesRel();
	}
	else if (relation_name == "MODIFIES") {
		return ParseModifiesRel();
	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - unidentifiable relRef: " + relation_name);
	}
}

shared_ptr<Rel> QueryBuilder::ParseUsesRel() {
	shared_ptr<Ref> lhs_syn;
	shared_ptr<Ref> rhs_syn;
	if (lexer_->HasIdentity()) {
		lhs_syn = GetNextStmtRef();
	}
	else {
		lhs_syn = GetNextProcRef();
	}

	lexer_->MatchCommaDelimeter();

	rhs_syn = GetNextVarRef();
	if (lhs_syn->GetRefType() == RefType::kProcRef) {
		return shared_ptr<Rel>(new UsesPRel(std::dynamic_pointer_cast<ProcRef>(lhs_syn), std::dynamic_pointer_cast<VarRef>(rhs_syn)));
	}
	else {
		
		shared_ptr<StmtRef> lhs_var_syn = std::dynamic_pointer_cast<StmtRef>(lhs_syn);
		shared_ptr<VarRef> rhs_var_syn = std::dynamic_pointer_cast<VarRef>(rhs_syn);
		string s = rhs_var_syn->TestString();

		return shared_ptr<Rel>(new UsesSRel(std::dynamic_pointer_cast<StmtRef>(lhs_syn), std::dynamic_pointer_cast<VarRef>(rhs_syn)));
	}
}

shared_ptr<Rel> QueryBuilder::ParseModifiesRel() {
	shared_ptr<Ref> lhs_syn;
	shared_ptr<Ref> rhs_syn;
	if (lexer_->HasIdentity()) {
		lhs_syn = GetNextStmtRef();
	}
	else {
		lhs_syn = GetNextProcRef();
	}

	lexer_->MatchCommaDelimeter();

	rhs_syn = GetNextVarRef();

	if (lhs_syn->GetRefType() == RefType::kProcRef) {
		return shared_ptr<Rel>(new ModifiesPRel(std::dynamic_pointer_cast<ProcRef>(lhs_syn), std::dynamic_pointer_cast<VarRef>(rhs_syn)));
	}
	else {
		return shared_ptr<Rel>(new ModifiesSRel(std::dynamic_pointer_cast<StmtRef>(lhs_syn), std::dynamic_pointer_cast<VarRef>(rhs_syn)));
	}
}

std::pair<shared_ptr<Ref>, shared_ptr<Ref>> QueryBuilder::GetModifiesOrUsesSyns() {
	shared_ptr<Ref> lhs_syn;
	shared_ptr<Ref> rhs_syn;
	if (lexer_->HasIdentity()) {
		lhs_syn = GetNextStmtRef();
	}
	else {
		lhs_syn = GetNextProcRef();
	}

	lexer_->MatchCommaDelimeter();

	rhs_syn = GetNextVarRef();
	return { lhs_syn, rhs_syn };
}

//shared_ptr<Ref> QueryBuilder::ParseNextRef() {
//	if (this->lexer_->HasIdentity()) {
//		std::string identity = this->lexer_->MatchIdentity();
//		shared_ptr<Ref> ref = GetDeclaredSyn(identity);
//		return ref;
//	}
//	else if (this->lexer_->HasInteger()) {
//		int statement_number_ = this->lexer_->MatchInteger();
//		shared_ptr<Ref> ref = std::make_shared<StmtRef>(ValType::kLineNum, std::to_string(statement_number_));
//		return ref;
//	}
//	else if (this->lexer_->HasQuotationMarks()) {
//		this->lexer_->MatchQuotationMarks();
//		if (this->lexer_->HasIdentity()) {
//			std::string identity_ = this->lexer_->MatchIdentity();
//			ProcRef* lhs_ = new ProcRef(ValType::kProcName, identity_);
//			if (this->lexer_->HasQuotationMarks()) {
//				this->lexer_->MatchQuotationMarks();
//				shared_ptr <VarRef> rhs_ = GetRhsVarRef(synonyms_);
//				return shared_ptr<Rel>(new UsesPRel(*lhs_, *rhs_));
//			}
//			else {
//				throw SyntaxError("Select statement - [suchthatcl] - missing ending quotation marks at end of identity token");
//			}
//		}
//		else {
//			throw SyntaxError("Select statement - [suchthatcl] - invalid identity token inside quotes");
//		}
//	}
//	else if (this->lexer_->HasUnderScore()) {
//		this->lexer_->MatchUnderScore();
//		throw SyntaxError("Select statement - [suchthatcl] - WildCard cannot be on lhs of Uses Relation");
//	}
//	else {
//		throw SyntaxError("Select statement - [suchthatcl] - Unable to parse USES relation");
//	}
//
//
//}

shared_ptr<Ref> QueryBuilder::GetNextStmtRef() {
	shared_ptr<Ref> stmt_ref;
	if (lexer_->HasInteger()) {
		int line_number = lexer_->MatchInteger();
		stmt_ref = std::make_shared<StmtRef>(ValType::kLineNum, std::to_string(line_number));
	}
	else if (lexer_->HasUnderScore()) {
		lexer_->MatchUnderScore();
		stmt_ref = std::make_shared<StmtRef>(ValType::kWildcard, "");
	}
	else if (lexer_->HasIdentity()) {
		string ref_name = lexer_->MatchIdentity();
		stmt_ref = GetDeclaredSyn(ref_name, RefType::kStmtRef);
	}
	else {
		throw SyntaxError("Incorrect Reference Type: Not a stmt type");
	}
	return stmt_ref;
};

shared_ptr<Ref> QueryBuilder::GetNextProcRef() {
	shared_ptr<Ref> proc_ref;
	if (lexer_->HasQuotationMarks()) {
		lexer_->MatchQuotationMarks();
		string proc_name = lexer_->MatchIdentity();
		lexer_->MatchQuotationMarks();
		proc_ref = std::make_shared<ProcRef>(ValType::kProcName, proc_name);
	}
	else if (lexer_->HasUnderScore()) {
		lexer_->MatchUnderScore();
		proc_ref = std::make_shared<ProcRef>(ValType::kWildcard, "");
	}
	else if (lexer_->HasIdentity()) {
		string proc_name = lexer_->MatchIdentity();
		proc_ref = GetDeclaredSyn(proc_name, RefType::kProcRef);
	}
	else {
		throw SyntaxError("Incorrect Reference Type: Not a Proc type");
	}
	return proc_ref;
}

shared_ptr<Ref> QueryBuilder::GetNextVarRef() {
	shared_ptr<Ref> var_ref;
	if (lexer_->HasQuotationMarks()) {
		lexer_->MatchQuotationMarks();
		string var_name = lexer_->MatchIdentity();
		lexer_->MatchQuotationMarks();
		var_ref = std::make_shared<VarRef>(ValType::kVarName, var_name);
	}
	else if (lexer_->HasUnderScore()) {
		lexer_->MatchUnderScore();
		var_ref = std::make_shared<VarRef>(ValType::kWildcard, "");
	}
	else if (lexer_->HasIdentity()) {
		string var_name = lexer_->MatchIdentity();
		var_ref = GetDeclaredSyn(var_name, RefType::kVarRef);
	}
	else {
		throw SyntaxError("Incorrect Reference Type: Not a Var type");
	}
	return var_ref;
}
//shared_ptr<Ref> QueryBuilder::GetNextConstRef() {
//	
//}



shared_ptr<Ref> QueryBuilder::GetDeclaredSyn(string name) {
	for (shared_ptr<Ref> synonym : synonyms_) {
		if (synonym->GetName() == name) {
			return synonym;
		}
	}
	throw SemanticError("Synonym " + name + " is not declared before use.");
}

shared_ptr<Ref> QueryBuilder::GetDeclaredSyn(string name, RefType ref_type) {
	for (shared_ptr<Ref> synonym : synonyms_) {
		if (synonym->GetName() == name) {
			if (synonym->GetRefType() == ref_type) {
				return synonym;
			}
			else if (synonym->GetRefType() == RefType::kStmtRef && stmt_ref_types.count(synonym->GetRefType())) {
				return synonym;
			}
			else {
				throw SemanticError("Type of synonym " + name + " is unmatched to declared type");
			}
			 
		}
	}
	throw SemanticError("Synonym " + name + " is not declared before use.");
}


shared_ptr<VarRef> QueryBuilder::GetRhsVarRef(std::vector<shared_ptr<Ref>> synonyms_) {
	if (this->lexer_->HasCommaDelimeter()) {
		this->lexer_->MatchCommaDelimeter();
	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - missing comma (,) between LHS and RHS of relRef");
	}

	if (this->lexer_->HasIdentity()) {
		std::string identity_rhs_ = this->lexer_->MatchIdentity();
		for (shared_ptr<Ref> synonym_var_rhs_ : synonyms_) {

			if (synonym_var_rhs_->GetValType() == ValType::kSynonym && synonym_var_rhs_->GetRefType() == RefType::kVarRef && synonym_var_rhs_->GetName().compare(identity_rhs_) == 0) {
				shared_ptr <VarRef> rhs_ = std::dynamic_pointer_cast<VarRef>(synonym_var_rhs_);
				return rhs_;
			}
		}
		throw SyntaxError("Select statement - [suchthatcl] - no valid var synonym found on rhs of relRef");
	}
	else if (this->lexer_->HasQuotationMarks()) {
		this->lexer_->MatchQuotationMarks();
		if (this->lexer_->HasIdentity()) {
			shared_ptr <VarRef> rhs_ = shared_ptr <VarRef>(new VarRef(ValType::kVarName, this->lexer_->MatchIdentity()));
			return rhs_;
		}
		else {
			throw SyntaxError("Select statement - [suchthatcl] - invalid identity token inside quotes");
		}

	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - invalid token on RHS of relRef ");
	}
}


//Continue working on parsing pattern clause

std::vector <shared_ptr<Pattern>> QueryBuilder::ParsePatterns() {
	std::vector<shared_ptr<Pattern>> patterns_;
	//if (HasPatternClause()) {
	//	this->lexer_->MatchPatternKeyword();
	//	if (this->lexer_->HasIdentity()) {
	//		std::string syn_assign = this->lexer_->MatchIdentity();
	//		if (this->lexer_->HasOpeningBrace()) {
	//			this->lexer_->MatchOpeningBrace();
	//			if (this->lexer_->HasQuotation()) {
	//				this->lexer_->MatchQuotation();
	//				if (this->lexer_->HasIdentity()) {
	//					std::string identity_ = this->lexer_->MatchIdentity();
	//					if (this->lexer_->HasQuotation()) {
	//						this->lexer_->MatchQuotation();

	//						if (this->lexer_->HasCommaDelimeter()) {
	//							this->lexer_->MatchCommaDelimeter();
	//							if (this->lexer_->HasExpressionSpec()) {
	//								std::string expression_spec = this->lexer_->MatchExpressionSpec();
	//								if (this->lexer_->HasClosingBrace()) {
	//									this->lexer_->MatchClosingBrace();
	//									//return expression clause
	//								}
	//								else {
	//									//throw invalid syntax exception - missing closing brace 
	//								}
	//							}
	//							else {
	//								//Throw missing expressions spec
	//							}
	//						}
	//						else {
	//							//Syntax exception - Invalid pattern caluse missing comma delimeter
	//						}
	//					}
	//				}
	//				else {
	//					//Invalid entref
	//				}
	//			}
	//			else if (this->lexer_->HasIdentity()) {
	//				std::string identity_ =  this->lexer_->MatchIdentity();
	//				if (this->lexer_->HasCommaDelimeter()) {
	//					this->lexer_->MatchCommaDelimeter();
	//					if (this->lexer_->HasExpressionSpec()) {
	//						std::string expression_spec = this->lexer_->MatchExpressionSpec();
	//						if (this->lexer_->HasClosingBrace()) {
	//							this->lexer_->MatchClosingBrace();
	//							//return the parsed expression clause
	//						}
	//						else {
	//							//Invalid Syntax - missing closing brace
	//						}
	//					}
	//					else {
	//						//throw exception Missing Expression Spec
	//					}

	//				}
	//				else {
	//					//Syntax exception - Invalid pattern caluse missing comma delimeter
	//				}
	//			}
	//			else {
	//				//Invalid entRef 
	//			}

	//		}
	//		else {
	//			//throw an invalid syntax exception - Missing Opening Brace

	//		}
	//		 
	//	}
	//	else {
	//		//throw an invalid syntax exception - syn-assign not found
	//	}

	//} 

	return patterns_;
}




