#include "SemanticError.h"

SemanticError::SemanticError(std::string message) {
	this->message = message;
}

std::string SemanticError::what() const throw() {
	return "Invalid Query Semantic: " + this->message;
}