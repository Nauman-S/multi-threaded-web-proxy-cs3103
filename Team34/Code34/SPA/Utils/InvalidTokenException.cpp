#include "InvalidTokenException.h"

InvalidTokenException::InvalidTokenException(char unidentifiable_character) : SyntaxError(std::to_string(unidentifiable_character)) {
	this->unidentifiable_character = unidentifiable_character;
}

const char* InvalidTokenException::what() const throw ()
{
	return "Invalid token encountered : " + unidentifiable_character;
}