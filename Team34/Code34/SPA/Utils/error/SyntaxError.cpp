#include "SyntaxError.h"

#include <iostream>
#include <string>

SyntaxError::SyntaxError(std::string message) {
	this->message = message;
}

std::string SyntaxError::what() const throw() {
	return "Invalid Query Syntax: " + this->message;
}
