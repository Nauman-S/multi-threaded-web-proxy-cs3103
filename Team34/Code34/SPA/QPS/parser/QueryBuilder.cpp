#include "QueryBuilder.h"

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <memory>

#include "SyntaxError.h"
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

QueryBuilder::QueryBuilder() {
	this->lexer_ = new QueryLexer();
}

std::optional<Query*> QueryBuilder::GetQuery(const std::string& query_string_) {
		this->lexer_->FeedQuery(query_string_);
		std::vector<Ref*> synonyms_ = ParseDeclarationStatements();
		Query* query_ = ParseSelectStatement(synonyms_);
		return query_;
}

std::vector<Ref*> QueryBuilder::ParseDeclarationStatements() {
	std::vector<Ref*> synonyms;
	Ref* synonym_;

	while (this->lexer_->HasDesignEntity()) {
		synonym_ = ParseDeclarationStatement();
		synonyms.push_back(synonym_);
	}

	return synonyms;
}



Ref* QueryBuilder::ParseDeclarationStatement() {
	std::string design_entity_ = this->lexer_->MatchDesignEntityKeyword();

	if (this->lexer_->HasIdentity()) {
		std::string synonym_ = this->lexer_->MatchIdentity();

		if (this->lexer_->HasEndOfDeclarationStatement()) {
			this->lexer_->MatchEndOfDeclarationStatement();
			Ref* ref_ = CreateReference(design_entity_, synonym_);
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

//this should be inside Create Ref class based on factory pattern. for now its here
Ref* QueryBuilder::CreateReference(std::string design_entity_, std::string synonym_) {

	if (design_entity_.compare("STMT") == 0) {
		return new StmtRef(ValType::kSynonym, synonym_);
	}
	else if (design_entity_.compare("READ") == 0) {
		return new ReadRef(ValType::kSynonym, synonym_);

	}
	else if (design_entity_.compare("PRINT") == 0) {
		return new PrintRef(ValType::kSynonym, synonym_);
	}
	else if (design_entity_.compare("CALL") == 0) {
		return new CallRef(ValType::kSynonym, synonym_);
	}
	else if (design_entity_.compare("WHILE") == 0) {
		return new WhileRef(ValType::kSynonym, synonym_);
	}
	else if (design_entity_.compare("IF") == 0) {
		return new IfRef(ValType::kSynonym, synonym_);
	}
	else if (design_entity_.compare("ASSIGN") == 0) {
		return new AssignRef(ValType::kSynonym, synonym_);
	}
	else if (design_entity_.compare("VARIABLE") == 0) {
		return new VarRef(ValType::kSynonym, synonym_);
	}
	else if (design_entity_.compare("CONSTANT") == 0) {
		return new ConstRef(ValType::kSynonym, synonym_);
	}
	else if (design_entity_.compare("PROCEDURE") == 0) {
		return new ProcRef(ValType::kSynonym, synonym_);
	}
	else {
		throw new SyntaxError("This error should never be called - Iconsistent Naming OF design_entities");
	}

}

Query* QueryBuilder::ParseSelectStatement(std::vector<Ref*> synonyms_) {

	if (this->lexer_->HasKeyword("SELECT")) {
		this->lexer_->MatchKeyword();
		std::vector<Ref*> select_tuple_ = ParseReturnValues(synonyms_);
		std::vector<Rel*> relations_ = ParseRelations(synonyms_);
		std::vector<Pattern*> patterns_ = ParsePatterns();

		if (this->lexer_->HasMoreTokens()) {
			throw SyntaxError("Unexpected token at end of query");
		}

		std::vector<std::shared_ptr<Ref>> select_tuple_s_;
		for (Ref* ref_ : select_tuple_) {
			std::shared_ptr <Ref> ref_s_ = std::shared_ptr<Ref>(ref_);
			select_tuple_s_.push_back(ref_s_);
		}

		std::vector<std::shared_ptr<Rel>> relations_s_;
		for (Rel* rel_ : relations_) {
			std::shared_ptr <Rel> rel_s_ = std::shared_ptr<Rel>(rel_);
			relations_s_.push_back(rel_s_);
		}

		std::vector<std::shared_ptr<Pattern>> patterns_s_;
		for (Pattern* pattern_ : patterns_) {
			std::shared_ptr <Pattern> pattern_s_ = std::shared_ptr<Pattern>(pattern_);
			patterns_s_.push_back(pattern_s_);
		}

		Query* query = new Query();
		return query;
	}
	else {
		throw SyntaxError("Select Statment - Missing (select) keyword");
	}
}

std::vector<Ref*> QueryBuilder::ParseReturnValues(std::vector<Ref*> synonyms) {
	std::vector<Ref*> select_tuple_;

	if (this->lexer_->HasIdentity()) {
		std::string identity_ = this->lexer_->MatchIdentity();

		for (Ref* ref : synonyms) {
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
		this->lexer_->MatchKeyword();
		if (this->lexer_->HasKeyword("THAT")) {
			this->lexer_->MatchKeyword();
			return true;
		}
	}

	return false;
}


//Continue from here
std::vector <Rel*> QueryBuilder::ParseRelations(std::vector<Ref*> synonyms_) {
	std::vector<Rel*> relations_;
	if (!HasSuchThatClause()) {
		return relations_;
	}

	std::string relation_reference_;
	if (this->lexer_->HasReferenceKeyword()) {
		relation_reference_ = this->lexer_->MatchReferenceKeyword();
	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - no valid relRef keyword found in such that clause");
	}

	if (this->lexer_->HasOpeningBrace()) {
		this->lexer_->MatchOpeningBrace();
	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - missing opening brace after relRef keyword");
	}

	//ParseRelation the relation clause
	Rel* rel_ref_clause_ = ParseRelRefClause(relation_reference_, synonyms_);


	if (this->lexer_->HasClosingBrace()) {
		this->lexer_->MatchClosingBrace();
	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - missing closing brace after relRef clause");
	}

	relations_.push_back(rel_ref_clause_);

	return relations_;
}

Rel* QueryBuilder::ParseRelRefClause(std::string relational_reference_, std::vector<Ref*> synonyms_) {
	std::set <std::string> stmt_ref_ = { "FOLLOWS", "FOLLOWS*", "PARENT", "PARENT*", "MODIFIES" };


	if (stmt_ref_.find(relational_reference_) != stmt_ref_.end()) {
		throw SyntaxError("FOLLOWS, FOLLOWS*, PARENT, PARENT*, MODIFIES have not yet been implemented");
	}
	else if (relational_reference_.compare("USES") == 0) {
			if (this->lexer_->HasIdentity()) {
				std::string identity_ = this->lexer_->MatchIdentity();
				for (Ref* synonym_lhs_ : synonyms_) {
					if (synonym_lhs_->GetValType() == ValType::kSynonym && synonym_lhs_->GetName().compare(identity_) == 0) {
						if (synonym_lhs_->GetRefType() == RefType::kAssignRef) {
							AssignRef* lhs_ = (AssignRef*)synonym_lhs_;
							VarRef* rhs_ = GetRhsVarRef(synonyms_);
							return new UsesSRel(*lhs_, *rhs_);
						}
						else if (synonym_lhs_->GetRefType() == RefType::kPrintRef) {
							PrintRef* lhs_ = (PrintRef*)synonym_lhs_;
							VarRef* rhs_ = GetRhsVarRef(synonyms_);
							return new UsesSRel(*lhs_, *rhs_);
						}
						else if (synonym_lhs_->GetRefType() == RefType::kIfRef) {
							IfRef* lhs_ = (IfRef*)synonym_lhs_;
							VarRef* rhs_ = GetRhsVarRef(synonyms_);
							return new UsesSRel(*lhs_, *rhs_);
						}
						else if (synonym_lhs_->GetRefType() == RefType::kWhileRef) {
							WhileRef* lhs_ = (WhileRef*)synonym_lhs_;
							VarRef* rhs_ = GetRhsVarRef(synonyms_);
							return new UsesSRel(*lhs_, *rhs_);
						}
						else if (synonym_lhs_->GetRefType() == RefType::kProcRef) {
							ProcRef* lhs_ = (ProcRef*)synonym_lhs_;
							VarRef* rhs_ = GetRhsVarRef(synonyms_);
							return new UsesPRel(*lhs_, *rhs_);
						}
					}
				}
				throw SyntaxError("Select statement - [suchthatcl] - no valid var synonym found on lhs of relRef");
			}
			else if (this->lexer_->HasInteger()) {
				int statement_number_ = this->lexer_->MatchInteger();
				StmtRef* lhs_ = new StmtRef(ValType::kLineNum, std::to_string(statement_number_));
				VarRef* rhs_ = GetRhsVarRef(synonyms_);
				return new UsesSRel(*lhs_, *rhs_);
			}
			else if (this->lexer_->HasQuotationMarks()) {
				this->lexer_->MatchQuotationMarks();
				if (this->lexer_->HasIdentity()) {
					std::string identity_ = this->lexer_->MatchIdentity();
					ProcRef* lhs_ = new ProcRef(ValType::kProcName, identity_);
					if (this->lexer_->HasQuotationMarks()) {
						this->lexer_->MatchQuotationMarks();
						VarRef* rhs_ = GetRhsVarRef(synonyms_);
						return new UsesPRel(*lhs_, *rhs_);
					}
					else {
						throw SyntaxError("Select statement - [suchthatcl] - missing ending quotation marks at end of identity token");
					}
				}
				else {
					throw SyntaxError("Select statement - [suchthatcl] - invalid identity token inside quotes");
				}
			}
			else if (this->lexer_->HasUnderScore()) {
				this->lexer_->MatchUnderScore();
				throw SyntaxError("Select statement - [suchthatcl] - WildCard cannot be on lhs of Uses Relation");
			}
			else {
				throw SyntaxError("Select statement - [suchthatcl] - Unable to parse USES relation");
			}
	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - unidentifiable relRef: " + relational_reference_);
	}
}

VarRef* QueryBuilder::GetRhsVarRef(std::vector<Ref*> synonyms_) {
	if (this->lexer_->HasCommaDelimeter()) {
		this->lexer_->MatchCommaDelimeter();
	}
	else {
		throw SyntaxError("Select statement - [suchthatcl] - missing comma (,) between LHS and RHS of relRef");
	}

	if (this->lexer_->HasIdentity()) {
		std::string identity_rhs_ = this->lexer_->MatchIdentity();
		for (Ref* synonym_var_rhs_ : synonyms_) {

			if (synonym_var_rhs_->GetValType() == ValType::kSynonym && synonym_var_rhs_->GetRefType() == RefType::kVarRef && synonym_var_rhs_->GetName().compare(identity_rhs_) == 0) {
				VarRef* rhs_ = (VarRef*)synonym_var_rhs_;
				return rhs_;
			}
		}
		throw SyntaxError("Select statement - [suchthatcl] - no valid var synonym found on rhs of relRef");
	}
	else if (this->lexer_->HasQuotationMarks()) {
		this->lexer_->MatchQuotationMarks();
		if (this->lexer_->HasIdentity()) {
			VarRef* rhs_ = new VarRef(ValType::kVarName, this->lexer_->MatchIdentity());
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

std::vector <Pattern*> QueryBuilder::ParsePatterns() {
	std::vector<Pattern*> patterns_;
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




